# **Controle de LEDs com Teclado Matricial - Projeto EmbarcaTech**

## **Descrição**
Este projeto foi desenvolvido para a EmbarcaTech e demonstra o controle de três LEDs (vermelho, verde e azul) usando um teclado matricial 4x4 conectado à Raspberry Pi Pico. Cada tecla do teclado acende um LED correspondente:
- **Tecla `1`**: Liga o LED vermelho.
- **Tecla `2`**: Liga o LED verde.
- **Tecla `3`**: Liga o LED azul.

O projeto foi simulado utilizando o [Wokwi](https://wokwi.com/), um simulador de hardware online.

---

## **Funcionamento do Código**
1. **Inicialização do Teclado Matricial**:
   - O teclado matricial é configurado utilizando pinos GPIO da Raspberry Pi Pico. As linhas são configuradas como saídas e as colunas como entradas com resistores de pull-down.
   - A função `init_keypad()` realiza esta configuração.

2. **Leitura do Teclado**:
   - A função `get_key()` percorre cada linha, ativando-a (colocando o sinal lógico em baixo) e verificando se há um sinal em alguma coluna. Caso uma tecla seja pressionada, o caractere correspondente é retornado.

3. **Controle dos LEDs**:
   - A função `handle_key()` recebe a tecla pressionada e acende o LED correspondente. Antes disso, todos os LEDs são apagados para evitar sobreposição.

4. **Loop Principal**:
   - No `main()`, o código inicializa o teclado e os LEDs. Em seguida, entra em um loop infinito, onde verifica constantemente as teclas pressionadas e executa as ações correspondentes.

---

## **Requisitos**
- [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)
- Simulador [Wokwi](https://wokwi.com/)
- Ambiente de desenvolvimento configurado com Pico SDK.

---

## **Passos para Clonar e Compilar**
1. Clone o repositório:
   ```bash
   git clone <URL_DO_REPOSITORIO>
   cd <NOME_DO_REPOSITORIO>
   mkdir build
   cd build
   cmake ..
   ninja
   ```

2. Carregue o binário gerado no hardware ou simule no Wokwi.

---

## **Vídeo Demonstrativo**
Assista ao vídeo que demonstra o funcionamento do projeto:  
[![Demonstração do Projeto](https://img.youtube.com/vi/IcO5D7BfMXI/0.jpg)](https://youtu.be/IcO5D7BfMXI)  
Link: [https://youtu.be/IcO5D7BfMXI](https://youtu.be/IcO5D7BfMXI)

---
