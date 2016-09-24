# ticket_based_authentication_protocol

[Anonymous Ticket-Based Authentication]

1) 과제 목적
주어진 명세 및 요구사항을 따르는 시스템의 요구분석, 설계, 구현, 시험하는 전 과정을 스스로 수행함으로써 암호화 기법과 이를 응용한 보안 프로토콜 시스템의 설계 및 구현 능력을 키운다. 


2) 과제 개요

다양한 암호화 기법들을 활용하여 맨 처음 공개키 암호화 방식으로 인증 받은 사용자가 이후 서버로부터 받은 인증티켓을 사용하여 인증 받는 프로토콜의 상세 설계와 구현


3) 프로토콜
  o. 가정
 -  인증 서버(이하 Bob)는 다수 사용자의 인증을 담당하는데, 각 사용자의 certificate를 검증하기 위해서 CA의 public key를 보유하고 있다.
 - 각 사용자는 CA에 의해 발급된 다음과 같은 certificate를 소유하고 있다. 예를 들어, Alice의 certificate는 =("Alice", Alice의 public key) 및 로 구성되어 있다. Certificate에는 소유자 명칭이 hash 함수 적용된 채 저장되어 있어, certificate를 통해서는 그 소유자(사용자)를 알 수 없다. 각 사용자의 명칭은 예측 불가능하기 때문에 forward search는 불가능하다.
-  사용자, Bob 모두 RC4, AES, RSA, SHA-2 를 각각 사용할 수 있으며, 키(key)의 길이 등은 이미 사용자와 Bob 사이에 서로 합의된 값이 존재한다.
-  키 및 nonce 값들은 모두 RC4 알고리즘에 의해 생성된다.
