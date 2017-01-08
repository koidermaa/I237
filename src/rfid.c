#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "hmi_msg.h"
#include "rfid.h"
#include "../lib/matejx_avr_lib/mfrc522.h"

void rfid_list_cards(void);
card_t *head = NULL;

typedef struct card {
    uint8_t uid_size;
    uint8_t uid[10];
    char *user;
    struct card *next;
} card_t;


void rfid_add_card(const char *user)
{
    Uid uid;
    card_t *head = NULL;
    head = malloc(sizeof(card_t));
    if (head == NULL) {
        printf_P(PSTR(MEM_FAIL_MSG"\n"));
        //free(head);
        return;
    }
    
    if (PICC_IsNewCardPresent()) {
        PICC_ReadCardSerial(&uid);

        head->uid_size = uid.size;
        head->user = malloc(strlen(user) + 1);
        memcpy(head->uid, &uid.uidByte, uid.size);
        head->next = NULL;
        printf_P((PSTR("koostan kaardi \n")));
    } else {
        printf_P((PSTR(CARD_NOT_SELECTED"\n")));
    }
    rfid_list_cards();
}


void rfid_print_card(const card_t *card)
{
    for (uint8_t i = 0; i < card->uid_size; i++) {
        printf("%02X", card->uid[i]);
    }
    printf(": %s", card->user);
}


void rfid_list_cards(void)
{

    if (head == NULL) {
        printf_P(PSTR("Kaarte pole \n"));
    } else {
        card_t *current;
        current = head;
        while (current->next != NULL) {
            rfid_print_card(current);
            putc('\n', stdout);
            current = current->next;
        }
        rfid_print_card(current);
        putc('\n', stdout);
    }
}


