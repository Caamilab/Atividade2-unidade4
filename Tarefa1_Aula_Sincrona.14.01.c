#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"
#include <stdio.h>
// Definições de pinos
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER 21

// Inicialização dos LEDs e do buzzer
void init_gpio() {
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    pwm_set_wrap(slice_num, 12500); // (~2kHz para 125MHz clock)
    pwm_set_gpio_level(BUZZER, 0); // duty cycle off
    pwm_set_enabled(slice_num, false);
}

// Desliga todos os LEDs e o buzzer
void turn_off_all() {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

void activate_buzzer(uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);

    // Enable PWM 
    pwm_set_enabled(slice_num, true);
    pwm_set_gpio_level(BUZZER, 6250); // duty cycle 50%

    printf("Buzzer acionado por %d ms.\n", duration_ms);

    
    sleep_ms(duration_ms);

    
    pwm_set_enabled(slice_num, false);
}

// Função principal
int main() {
    
    stdio_init_all();
    sleep_ms(3000);
    
    init_gpio();
    turn_off_all();
    
     while (true) {
        printf("\nMenu de Comandos:\n");
        printf("1 - Ligar LED Verde\n");
        printf("2 - Ligar LED Azul\n");
        printf("3 - Ligar LED Vermelho\n");
        printf("4 - Ligar Todos os LEDs (Luz Branca)\n");
        printf("5 - Desligar Todos os LEDs\n");
        printf("6 - Acionar o Buzzer por 2 segundos\n");
        printf("7 - Reiniciar o Sistema\n");
        printf("Digite o comando: ");

        char command;
        scanf(" %c", &command); // Lê o comando do usuário
        turn_off_all(); // Desliga tudo antes de executar o comando

        switch (command) {
            case '1': // Liga LED verde
                gpio_put(LED_VERDE, 1);
                printf("LED Verde ligado.\n");
                break;
            case '2': // Liga LED azul
                gpio_put(LED_AZUL, 1);
                printf("LED Azul ligado.\n");
                break;
            case '3': // Liga LED vermelho
                gpio_put(LED_VERMELHO, 1);
                printf("LED Vermelho ligado.\n");
                break;
            case '4': // Liga todos os LEDs (luz branca)
                gpio_put(LED_VERDE, 1);
                gpio_put(LED_AZUL, 1);
                gpio_put(LED_VERMELHO, 1);
                printf("Todos os LEDs ligados (luz branca).\n");
                break;
            case '5': // Desliga todos os LEDs e o buzzer
                turn_off_all();
                printf("Todos os LEDs desligados.\n");
                break;
            case '6': // Aciona o buzzer por 2 segundos
                activate_buzzer(2000);
                break;
            case '7': // Reinicia o sistema (reboot)
                printf("Reiniciando o sistema...\n");
                reset_usb_boot(0, 0); // Reinicia no modo de gravação USB
                break;
            default:
                printf("Comando desconhecido. Tente novamente.\n");
                break;
        }

        sleep_ms(100); 
    }
}
