# Sistema de Irrigação Automática com Arduino

Este projeto implementa um Sistema de Irrigação Automática utilizando um Arduino Uno WiFi, integrado com o Node-RED para monitoramento e controle. O sistema é projetado para monitorar a umidade do solo e acionar a irrigação automaticamente quando necessário, garantindo a manutenção de níveis ótimos de umidade para o cultivo de plantas.

## Sumário

- [Introdução](#introdução)
- [Componentes Utilizados](#componentes-utilizados)
- [Instalação](#instalação)
- [Configuração do Node-RED](#configuração-do-node-red)
- [Uso](#uso)
- [Licença](#licença)

## Introdução

A irrigação eficiente é crucial para a agricultura sustentável. Este projeto visa automatizar o processo de irrigação usando um Arduino Uno WiFi para coletar dados de umidade do solo e um sistema de controle baseado no Node-RED para processar esses dados e acionar uma bomba de água quando necessário.

## Componentes Utilizados

- Arduino Uno WiFi
- Sensor de Umidade do Solo
- Relé ou Módulo de Controle de Bomba de Água
- Bomba de Água
- Node-RED
- Broker MQTT (HiveMQ)

## Instalação

### Hardware

1. **Conecte o Sensor de Umidade do Solo ao Arduino:**
   - VCC do sensor ao 5V do Arduino
   - GND do sensor ao GND do Arduino
   - Sinal do sensor a um pino analógico (A0) do Arduino

2. **Conecte o Módulo de Controle da Bomba de Água ao Arduino:**
   - VCC do módulo ao 5V do Arduino
   - GND do módulo ao GND do Arduino
   - Pino de controle ao pino digital (D7) do Arduino

### Software

1. **Configuração do Arduino:**
   - Carregue o firmware `StandardFirmata` na placa Arduino usando o Arduino IDE.
   - Certifique-se de que a placa Arduino está conectada à rede WiFi.

2. **Configuração do Node-RED:**
   - Instale o Node-RED na sua máquina. Siga as instruções em [Node-RED Getting Started](https://nodered.org/docs/getting-started/).
   - Adicione o nó `node-red-contrib-gpio` para integrar com o Arduino.
   - Configure o Node-RED para se comunicar com o Arduino via Firmata.

## Configuração do Node-RED

1. **Fluxo Básico:**
   - **Entrada de Dados:** Adicione um nó `analog input` para ler os dados do sensor de umidade do solo.
   - **Processamento:** Adicione um nó `function` para verificar o nível de umidade do solo.
   - **Saída de Controle:** Adicione um nó `digital output` para controlar a bomba de água.

2. **Configuração do MQTT:**
   - Configure um nó MQTT para enviar os dados de umidade do solo para o broker HiveMQ.
   - Configure um nó MQTT para receber comandos de controle remoto (se necessário).

### Exemplo de Fluxo no Node-RED:

```json
[
    {
        "id": "sensor",
        "type": "rpi-gpio in",
        "z": "a1b2c3d4",
        "name": "Sensor de Umidade",
        "pin": "A0",
        "intype": "analog",
        "debounce": "25",
        "read": "true",
        "x": 100,
        "y": 100,
        "wires": [["function-check"]]
    },
    {
        "id": "function-check",
        "type": "function",
        "z": "a1b2c3d4",
        "name": "Verificação de Umidade",
        "func": "if (msg.payload < 300) {\n    return { payload: 1 };\n} else {\n    return { payload: 0 };\n}",
        "outputs": 1,
        "noerr": 0,
        "x": 300,
        "y": 100,
        "wires": [["relay-control"]]
    },
    {
        "id": "relay-control",
        "type": "rpi-gpio out",
        "z": "a1b2c3d4",
        "name": "Controle da Bomba",
        "pin": "7",
        "set": true,
        "level": "0",
        "freq": "",
        "out": "out",
        "x": 500,
        "y": 100,
        "wires": []
    },
    {
        "id": "mqtt-out",
        "type": "mqtt out",
        "z": "a1b2c3d4",
        "name": "",
        "topic": "umidade",
        "qos": "",
        "retain": "",
        "broker": "mqtt-broker",
        "x": 500,
        "y": 200,
        "wires": []
    }
]

## Uso

1. **Inicie o Node-RED:** Execute o comando `node-red` no terminal.
2. **Acesse a Interface Web:** Abra o navegador e vá para [http://localhost:1880](http://localhost:1880)
3. **Implante o Fluxo:** Carregue o fluxo JSON no Node-RED e clique em "Deploy".
4. **Monitore e Controle:** Verifique a umidade do solo e o status da bomba de água pelo dashboard do Node-RED.

## Licença

Este projeto é licenciado sob os termos da licença MIT. Veja o arquivo LICENSE para mais detalhes.

---

**Nota:** Este projeto foi desenvolvido como parte de um trabalho acadêmico na Universidade Presbiteriana Mackenzie (UPM). Para mais informações, consulte os autores Evelin Aparecida Oliveira Lopes e Elias Junior Alves.
