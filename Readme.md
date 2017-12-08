Датчик мониторинга парковочных мест
===================================
Принимаемые сообщения:
-----------------------------------
### 1. Изменить ID
* **Пакет:**  
    uint32_t ID | uint8_t type | uint32_t newID  
    \x00\x00\x00\x01\i\x00\x00\x00\x02

* **UART пакет:**  
    uint8_t len | uint32_t ID | uint8_t type | uint32_t newID  
    \x09\x00\x00\x00\x01\i\x00\x00\x00\x02

### 2. Изменить период опроса сенсоров
* **Пакет:**  
    uint32_t ID | uint8_t type | uint16_t period  
    \x00\x00\x00\x01\s\x00\x64

* **UART пакет:**  
    uint8_t len | uint32_t ID | uint8_t type | uint16_t  
    \x07\x00\x00\x00\x01\s\x00\x64

### 3. Изменить период отправки сообщений "Статус"
* **Пакет:**  
    uint32_t ID | uint8_t type | uint16_t period  
    \x00\x00\x00\x01\p\x03\xE8

* **UART пакет:**  
    uint8_t len | uint32_t ID | uint8_t type | uint16_t period  
    \x07\x00\x00\x00\x01\p\x03\xE8

### 4. Забронировать парковочное место
* **Пакет:**  
    uint32_t ID | uint8_t type | uint8_t placeId | uint16_t period  
    \x00\x00\x00\x01\r\x00\x00\x14

* **UART пакет:**  
    uint8_t len | uint32_t ID | uint8_t type | uint8_t placeId | uint16_t period  
    \x08\x00\x00\x00\x01\r\x00\x00\x14

### 5. Отмена бронирования парковочного места
* **Пакет:**  
    uint32_t ID | uint8_t type | uint8_t placeId  
    \x00\x00\x00\x01\c\x00

* **UART пакет:**  
    uint8_t len | uint32_t ID | uint8_t type | uint8_t placeId  
    \x06\x00\x00\x00\x01\c\x00
