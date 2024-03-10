# 임피던스 장치를 위한 I2C통신의 프로토콜 정의 

### MASTER : Impedance Reader
### SLAVE : LCD DISPLAY, 프로토콜 변환기

### MASTER에서 SLAVE로 데이타를 전송하기 
- 읽어들인 내부저항 값을 전송한다
- 최대 1024 개의 byte data를 전송한다.( 512ms)
- packet 구조  
  * SenderId: 1Byte(modbus의 id와  대응)  
  * Command : 1Byte(modbus의 function과 대응)  
    1. V : Voltage 
    1. R : Impedance
    1. T : Temperature
  * start address: 2Byte  
  * length : 2Byte  
  * data : 248 byte(max), UINT 124 cell  
    - 전체 데이타는 순서대로 전송된다.() 
    - 위치을 포함한 데이타는 첫번째 바이트는 POSITION  
      두번째, 세번째 데이타는 Value를 의미 한다.
  * time : 현재의 시각( Uint32_t)
  * ex) 20개의 uint_16 전압 데이타를 전송  
    - V 0x00 0x00 0x00 0x24 0x-- 0x--......  
  * ex) 3번째 셀 의 uint_16 전압 데이타를 전송  
    - V 0x00 0x03 0x00 0x02 0x-- 0x--  

### MASTER에서 SLAVE로 데이타를 요청하기
  - 요청 데이타 : 시간정보 및 설정정보 등
    1. length : 16byte
      - LCD : 현재의 설정정보  
      - 프로토콜변환기: 현재의 시간
        unsigned long : 4byte

