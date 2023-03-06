/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/

void __udp_echoserver_receive_callback_oo(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

char recive_buff[6];

void __udp_echoserver_init_oo(void)
{
	struct udp_pcb *upcb;

	/* Create a new UDP control block  */
	upcb = udp_new();

	if (upcb)
	{
		/* Bind the upcb to the UDP_PORT port */
		/* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
		udp_bind(upcb, IP_ADDR_ANY, 61);
		udp_recv(upcb, __udp_echoserver_receive_callback_oo, NULL);
	}
}

void __udp_echoserver_receive_callback_oo( void* arg, // User argument - udp_recv `arg` parameter
                           struct udp_pcb* upcb,   // Receiving Protocol Control Block
                           struct pbuf* p,         // Pointer to Datagram
                           const ip_addr_t* addr,  // Address of sender
                           u16_t port )            // Sender port
{

	// Process datagram here (non-blocking code)
	strncpy(recive_buff, (char *)p->payload, p->len);

	// Must free receive pbuf before return
	pbuf_free(p);
}



