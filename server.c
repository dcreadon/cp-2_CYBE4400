

#include <assert.h>
#include <sel4/sel4.h>
#include <stdio.h>
#include <utils/util.h>

// cslot containing IPC endpoint capability
extern seL4_CPtr endpoint;
// cslot containing a capability to the cnode of the server
extern seL4_CPtr cnode;
// empty cslot
extern seL4_CPtr free_slot;

int main(int c, char *argv[]) {

	seL4_Word sender;
    seL4_MessageInfo_t info = seL4_Recv(endpoint, &sender);
    while (1) {
	    seL4_Error error;
        if (sender == 0) {

             /* No badge! give this sender a badged copy of the endpoint */
             seL4_Word badge = seL4_GetMR(0);
             
             // a copy of the shared enpoint is minted into free_slot to be sent
             seL4_Error error = seL4_CNode_Mint(cnode, free_slot, seL4_WordBits,
                                                cnode, endpoint, seL4_WordBits,
                                                seL4_AllRights, badge);
             printf("Badged %lu\n", badge);

             /* Here SetCap is being used to set the current badge capability of the connected client 
                free_slot will hold this capability which will then be sent back to the client. a reply_to_client 
                variable is declared which will be the reply sent to the client. This reply uses the messageinfo_new 
                function and specifies the third parameter which means that an extraCap will be sent */

	        seL4_SetCap(0, free_slot); 
	        seL4_MessageInfo_t reply_to_client = seL4_MessageInfo_new(0, 0, 1, 0);
	     
             /* reply to the sender and wait for the next message */
             //replace info with reply_to_client so we can send our response back
             seL4_Reply(reply_to_client);

             /* now delete the transferred cap */
             error = seL4_CNode_Delete(cnode, free_slot, seL4_WordBits);
             assert(error == seL4_NoError);

             /* wait for the next message */
             info = seL4_Recv(endpoint, &sender);
        } else {

             // TODO use printf to print out the message sent by the client
             // followed by a new line
             /* error variable is used here to hold the information from the first connected client. It utilized the free_slot
                hold the "reply capability" of the connected client. Next, a len variable is established to get the length of the current 
                message the client is trying to send which then gets fed into a for loop to print the current message of the connected client
                following that a seL4_Recv function is called to get the other client connected. Once this is done, a reply is sent to the first connected
                client so the second client can then send its message. This process then repeats until the clients are out of messages */
             error = seL4_CNode_SaveCaller(cnode, free_slot, seL4_WordBits);
             assert(error == 0);
             
             
             int len = seL4_MessageInfo_get_length(info);
             for (int i = 0; i < len; i++){
             	printf("%c", (char) seL4_GetMR(i));
             }
             printf("\n");
             
             info = seL4_Recv(endpoint, &sender);
             
             seL4_Send(free_slot, seL4_MessageInfo_new(0, 0, 0, 0));


	      
             /* Function necessary to complete task 3 but not needed for Task 4.
                Simply replies and receives a message in the same function.
                good for instantaneous response from the client.
                lets each client communicate before the other can.
                i.e clients communicate all messages in a row. */

             //info = seL4_ReplyRecv(endpoint, info, &sender);
        }
    }

    return 0;
}
