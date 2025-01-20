# Programa de Controle de LEDs e Buzzer no Raspberry Pi Pico W

Este programa foi desenvolvido para controlar três LEDs (verde, azul e vermelho) e um buzzer conectados ao Raspberry Pi Pico W. 

---

## Funcionalidades
- Ligar/desligar LEDs individualmente (verde, azul, vermelho).
- Ligar todos os LEDs simultaneamente (efeito de luz branca).
- Desligar todos os LEDs.
- Ativar o buzzer por 2 segundos.
- Reiniciar o sistema no modo de boot USB.

---

## Configuração dos Pinos
| Componente      | Pino GPIO |
|------------------|-----------|
| LED Verde        | GPIO 11   |
| LED Azul         | GPIO 12   |
| LED Vermelho     | GPIO 13   |
| Buzzer           | GPIO 21   |

---

## Explicação do Código

### 1. Inicialização
#### `init_gpio()`
- Configura os pinos GPIO dos LEDs como saídas.
- Configura o pino do buzzer (`GPIO 21`) como saída PWM.
- Define os parâmetros do PWM:
  - Frequência: ~2 kHz (usando `pwm_set_wrap` com valor `12500`).
  - Duty cycle: Inicialmente configurado como `0%` (desligado).
  - O PWM é desativado inicialmente (`pwm_set_enabled(slice_num, false)`).

#### `turn_off_all()`
- Desliga todos os LEDs configurando seus respectivos pinos GPIO para `LOW`.

---

### 2. Controle do Buzzer
#### `activate_buzzer(uint duration_ms)`
- Ativa o buzzer usando PWM:
  - Define o duty cycle como `50%` (`pwm_set_gpio_level`).
  - Habilita o slice do PWM que controla o buzzer (`pwm_set_enabled`).
- Mantém o buzzer ativo pelo tempo especificado (`duration_ms`) e depois desativa.

---

### 3. Funcionalidade Principal
#### `main()`
1. Inicializa a comunicação UART (`stdio_init_all`) para entrada/saída serial.
2. Aguarda 3 segundos para estabilizar a conexão USB serial.
3. Chama `init_gpio()` e `turn_off_all()` para preparar o hardware.

#### Loop do Menu
- Exibe continuamente um menu de comandos via UART:
    ```
    Menu de Comandos:
    1 - Ligar LED Verde
    2 - Ligar LED Azul
    3 - Ligar LED Vermelho
    4 - Ligar Todos os LEDs (Luz Branca)
    5 - Desligar Todos os LEDs
    6 - Acionar o Buzzer por 2 segundos
    7 - Reiniciar o Sistema
    Digite o comando:
    ```
- Lê a entrada do usuário usando `scanf` e processa com uma estrutura `switch`.

##### Comandos:
1. **Comando '1'**: Liga o LED verde (`gpio_put(LED_VERDE, HIGH)`).
2. **Comando '2'**: Liga o LED azul (`gpio_put(LED_AZUL, HIGH)`).
3. **Comando '3'**: Liga o LED vermelho (`gpio_put(LED_VERMELHO, HIGH)`).
4. **Comando '4'**: Liga todos os LEDs simultaneamente configurando todos os três pinos como `HIGH`.
5. **Comando '5'**: Desliga todos os LEDs chamando a função `turn_off_all()`.
6. **Comando '6'**: Ativa o buzzer por dois segundos chamando a função `activate_buzzer(2000)`.
7. **Comando '7'**: Reinicia o sistema no modo de boot USB usando `reset_usb_boot`.

##### Caso Padrão:
- Se um comando inválido for inserido, exibe a mensagem de erro: `"Comando desconhecido. Tente novamente."`

---

## Como Funciona
1. Conecte seu Raspberry Pi Pico W ao computador via USB.
2. Abra um terminal serial (ex.: PuTTY) e conecte-se à porta COM correta com taxa de transmissão de `115200`.
3. O programa exibirá um menu de comandos no terminal.
4. Insira um comando (ex.: `1` para ligar o LED verde) e observe seu efeito no hardware.

## Demonstração
https://youtu.be/gF1QTLroytw
