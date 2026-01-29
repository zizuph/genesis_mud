/*
 * 2003-09-17 by Dargoth
 * Provides base notarial messages used for getting forms or submitting docs
 * 
 */
#ifndef __NOTARY_SERVICE_DESC
#define __NOTARY_SERVICE_DESC

#define N_SIGN_TEXT ("The sign reads: \nWelcome to the Notarial Services!\n\n"+ \
    "Our office lets you easily create, securely sign, safely store\n"+ \
    "and comfortably retrieve documents for private and/or guild use.\n"+ \
    "The service features:\n"+ \
    " * document signing - any number of people can sign the document,\n"+ \
    "   their signature confirmed by a notary public, ensuring that they\n"+ \
    "   have really agreed to the document text.\n"+ \
    " * document storage - the signed agreements, contracts, etc. are\n"+ \
    "   stored safely in the Archives of Notarial service and can be\n"+ \
    "   consulted at any time.\n"+ \
    " * document retrieval - any of the parties who are marked as valid\n"+ \
    "   for viewing the particular document can freely request to see it\n"+ \
    "   at any time; or request an affirmed copy of the document (to carry\n"+ \
    "   away, all copies expire at Armageddon).\n"+ \
    " * sophisticated access - the documents can be marked as public, private\n"+ \
    "   guild access, or guild leaders only.\n\n"+ \
    "To put it bluntly, it acts almost as a shared mailbox with access control.\n\n"+ \
    "For more information read the poster in this room.\n")

#define N_SAY_PREFIX "The notary says to "


/* blank form get failures */
#define N_TOO_LOADED ("You fail to pick up the form because you are "+ \
    "too overloaded with things.\n")
#define N_FAIL_GET_SELF "You reach for the form, but somehow you can't get it.\n"
#define N_FAIL_GET_OTHERS (QCTNAME(TP)+" tries to get a notarial form, but fails.\n")
#define N_TOO_MANY_FORMS ("A beady looking official from behind the counter raises "+ \
   "a piercing gaze and tells you: I regret to inform you my "+ \
   "dear "+(TP->query_gender()?"lady":"sir")+", but there is a "+ \
   "limit to the number of forms you can take. Please come again "+ \
   "when you have made up your mind regarding the document "+ \
   "you wish to prepare.\n")
    
/* form get ok */
    
#define N_GET_OK_SELF "You pick up a blank notarial form.\n"
#define N_GET_OK_OTHERS (QCTNAME(TP)+" picks up a blank notarial form.\n")


/* examine messages */

#define N_SUBMIT_MSG_SELF ("You give the form to a notary behind the counter. "+ \
    "He purses his lips, and starts to examine it.\n")
#define N_SUBMIT_MSG_OTHERS (QCTNAME(TP)+" gives a notarial form "+ \
    "to one of the notaries behind the counter.\n")

/* submit failures */
#define N_FAIL_FORMVALUES1 "The notary shakes his head, and gives the form back to "
#define N_FAIL_FORMVALUES2 (" saying: Unfortunately, this form is not properly filled "+ \
    "out. The following is wrong: ")
#define N_FAIL_FORMVALUES3 ". Please correct the form and try again.\n"

#define N_FAIL_SUBMIT ("The notary tries to grope the document, but fails, "+ \
    "and it spurts away. Uh oh, seems this is another of them fabric of space "+ \
    "strangenesses.\n")

#define N_FAIL_NOMONEY ("The notary apologetically says "+ \
    "to you: You seem to lack the funds for storing any documents.\n")

/* submit ok messages */
#define N_FORM_OK1 ("The form appears to be in order; here is the document "+ \
	"proper. Now, if all the signers would please sign it and resubmit, "+ \
	"it will be ready for the Archives. Please submit a fully signed "+ \
	"document together with the processing fee.\n")
       
#define N_CHECK_OK ("The notary checks your form and carefully fills out "+ \
    "an official document based on it.\n")

#define N_SUBMIT_OK_SELF ("After accepting the fee, the notary turns away "+ \
	"to enter the document into the register.\n")
    
#define N_SUBMIT_OK_OTHERS (QCTNAME(TP)+" pays the fee and submits "+ \
    "a document for the archives.\n")

#define N_OK_REMINDER ("The notary turns back to you and says: "+ \
    "Thank you for using our services. "+ \
    "You should be able to access your "+ \
    "document now. "+ \
     "Please don't forget to pay the storage "+ \
    "fees for it within the next "+ \
    (INITIAL_EXPIRY/60)+" minutes, if "+ \
    "you wish to retain it.\n")
#endif
