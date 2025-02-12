# Vestido com Penas Animadas - retomada

## Introdução

Esta é uma retomada do projeto [Vestido com Penas Animadas](https://github.com/ksgomes1/trabalho_CF) com a finalidade de aperfeiçoar o dispositivo, o método de desenvolvimento e a documentação.

Na entrega original do projeto notou-se que o dispositivo tinha fragilidades. A base de tecido em que os motores estavam presos era muito maleável, os motores eram costurados à base, o que deixava os motores frouxos, o desenvolvimento teve atrasos pois há pouca informação sobre os contratempos que ocorreram com os servos e com o fornecimento de energia.

Nesta retomada haverá destaque na construção do dispositivo e no método de desenvolvimento do projeto e pouco destaque no desenvolvimento dos programas. O desenvolvimento será concentrado nos encontros presenciais. Estes iniciam com uma conversa sobre o que foi feito na reunião anterior, apresentação do que foi feito no intervalo entre a reunião anterior e a corrente, proposição de atividades para a reunião corrente, execução das atividades, apresentação de resultados das atividades da reunião corrente, definição e distribuição de tarefas (atividades) no intervalo até a próxima reunião (lição de casa) e atualização do diário (para posterior refinamento). Faz parte do método de desenvolvimento o registro de atividades (elaboração de um diário). O diário desta retomada está em [diario.md](./diario.md).    

<!---

## Materiais Utilizados

*   **Microcontrolador:** ESP32
*   **Servo Motores:** 12 servos motores SG90
*   **Mecanismos Pan-Tilt:** 6 mecanismos pan-tilt, cada um acoplado a um par de servo motores
*   **Fonte de Alimentação:** Fonte de alimentação externa (power bank) de 5V para os servos motores e o ESP32
*   **Fios e Conectores:** Para interligação dos componentes eletrônicos

## Mecanismo Pan-Tilt e Acoplamento com as Penas

O mecanismo pan-tilt é composto por dois servos motores conectados entre si por meio de uma estrutura mecânica que possibilita o movimento em dois eixos: horizontal (pan) e vertical (tilt). Neste projeto, cada mecanismo pan-tilt é acoplado a uma pena.

*   **Servo de Tilt (Levantamento):** Responsável pelo movimento vertical da pena, permitindo que ela seja levantada ou abaixada.
*   **Servo de Pan (Giro):** Responsável pelo movimento horizontal da pena, permitindo que ela gire para a esquerda ou para a direita.

## Funcionamento do Código

O código foi desenvolvido em C++, utilizando Arduino IDE, para o ESP32 e utiliza as seguintes bibliotecas:

*   `WiFi.h`: Para configurar o ESP32 como um Access Point (SoftAP) e permitir a conexão via Wi-Fi.
*   `ESPmDNS.h`: Para configurar o serviço mDNS, permitindo que o ESP32 seja acessado pelo nome "swan.local".
*   `ESPAsyncWebServer.h`: Para configurar um servidor web assíncrono no ESP32, que será utilizado para controlar os servos.
*   `ESP32Servo.h`: Para controlar os servo motores.

O código realiza as seguintes funções:

1.  **Configuração Inicial:**
    *   Inicializa a comunicação serial.
    *   Anexa os 12 servos motores aos pinos correspondentes do ESP32.
    *   Configura o ESP32 como um SoftAP (ponto de acesso Wi-Fi) com o nome "swan dress".
    *   Inicia o serviço mDNS para que o ESP32 possa ser acessado pelo endereço "swan.local".
    *   Cria um servidor web na porta 80.

2.  **Página Web:**
    *   Define uma página HTML simples com botões para controlar os servos.
    *   Os botões direcionam para URLs específicos que correspondem às funções de controle dos servos.

3.  **Rotas de Controle:**
    *   ` /turnon`: Levanta todas as penas, movendo os servos de tilt para a posição 100.
    *   ` /turndown`: Abaixa todas as penas, movendo os servos de tilt para a posição 10.
    *   ` /spinright`: Gira todas as penas para a direita, movendo os servos de pan para a posição 100.
    *   ` /spinleft`: Gira todas as penas para a esquerda, movendo os servos de pan para a posição 10.
    *   ` /off`: Para todos os servos, retornando-os à posição 0.
    *   Todas as rotas redirecionam o usuário de volta para a página principal após a execução.
    *   `notFound`: Retorna uma mensagem de erro 404 para URLs não reconhecidas.

4.  **Função `setServoPositions`:**
    *   Recebe um array de servos, o número de servos e a posição desejada.
    *   Itera sobre cada servo do array e move-o para a posição especificada, com um delay de 500ms.
    *   Verifica se cada servo está anexado antes de movê-lo, e imprime uma mensagem caso não esteja.

## App para controle dos motores

Um app foi construído utlizando MIT App Creator para o controle da movimentação dos motores em conjunto com o servidor web. É possível acessá-lo através do QR Code:

![image](https://github.com/user-attachments/assets/b1f43192-11d3-486e-84c6-dbc2fe5efde0)

## Pinagem dos Motores no ESP32

A pinagem utilizada para conectar os 12 servo motores ao ESP32 é a seguinte:

*   **Servos de Tilt (Levantamento):**
    *   Servo 1: Pino 13
    *   Servo 2: Pino 12
    *   Servo 3: Pino 14
    *   Servo 4: Pino 27
    *   Servo 5: Pino 26
    *   Servo 6: Pino 25
*   **Servos de Pan (Giro):**
    *   Servo 1: Pino 15
    *   Servo 2: Pino 2
    *   Servo 3: Pino 4
    *   Servo 4: Pino 5
    *   Servo 5: Pino 19
    *   Servo 6: Pino 21

## Considerações Finais

A combinação de microcontrolador, servos motores e mecanismos pan-tilt possibilitou a criação de movimentos complexos e expressivos nas penas. O uso de uma interface web ou app simples para o controle permite fácil manipulação dos movimentos, abrindo espaço para futuras melhorias e novas funcionalidades. Algumas melhorias serão necessárias para garantir o pleno funcionamento do projeto, como uma melhor otimização no consumo de energia do sistema.

Este relatório detalhou o processo de desenvolvimento, a descrição do mecanismo, o funcionamento do código e a pinagem utilizada.

--->

## Resultados

1. Documentação sobre funcionamento dos servos;
2. Documentação sobre instalação do driver Windows para ESP32 (usando chip CP210X - em contraposição a CH340 e FTDI232);
3. Nesta página (?)
   - teste do acionamento de um servo;
   - teste da fixação de um servo à base;
     - correções;
   - teste de levantamento da pena;               <- estamos aqui
   - teste da rotação da pena;                    <- estamos aqui
   - integração entre levantamento e rotação;
   - solução para fornecimento de energia;
   - construção de todos os conjuntos;
   - integração e teste integrado;
