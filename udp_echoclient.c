/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>
#include "lwip.h"

/* Private typedef -----------------------------------------------------------*/
struct udp_pcb *upcb;
extern uint8_t dest_status;
uint32_t port_oo = 0;

/* Private functions ---------------------------------------------------------*/
void __udp_echoclient_connect_oo(void){

	ip_addr_t DestIPaddr;

	udp_disconnect(upcb);
	udp_remove(upcb);

	upcb = udp_new();
	upcb->local_port = 62510;

	if(dest_status == 1){
//		PC IP1
		IP4_ADDR(&DestIPaddr, 10, 10, 2, 1);
		port_oo = 6661;
	}else{
//		PC IP2
		IP4_ADDR(&DestIPaddr, 10, 10, 2, 2);
		port_oo = 6662;
	}

	if (upcb!=NULL)
	{
		udp_connect(upcb, &DestIPaddr, port_oo);
	}
}


void __udp_echoclient_send_oo(char* udp_data_c){

	struct pbuf *p;

	/* allocate pbuf from pool*/
	p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)udp_data_c), PBUF_POOL);

	if (p != NULL)
	{
		/* copy data to pbuf */
		pbuf_take(p, (char*)udp_data_c, strlen((char*)udp_data_c));

		/* send udp data */
		udp_send(upcb, p);

		/* free pbuf */
		pbuf_free(p);
	}
}
