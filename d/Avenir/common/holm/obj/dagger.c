// fine old dagger       /d/Avenir/common/holm/obj/dagger.c
// creator(s):           Lilith, 1/25/97
// purpose:              To be wielded by Hunter shadow-elves
// last update:          Achdram, 1/23/2005 - Added adjectives
//                           "noble" and "shadow-elf". 
// note: 
// bug(s):
// to-do:
// ====== ========= ========= ========= ========= ========= ========= =====

inherit "/d/Avenir/inherit/weapon";
inherit "/lib/keep";
#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

string sigil, ad1, ad2;
string *adj1 = ({ "fine", "excellent", "superior", "nice", "grand",
                  "flawless", "superb" }),
       *adj2 = ({ "old", "classic", "antique" });

string query_sigil() {    return sigil;    }
void set_sigil(string str) {    sigil = str;    }

void configure_it ()
{
    if (!ad1) ad1 = adj1[random(sizeof(adj1))];
    if (!ad2) ad2 = adj2[random(sizeof(adj2))];
    add_adj(({ ad1, ad2, "noble", "shadow-elf"}));
    set_sigil(sigil);
    set_short(ad1 +" "+ ad2 +" dagger");  
    set_long("This dagger is both "+ ad1 +" and "+ ad2 +". It looks "+
           "like it has been passed down through several generations "+
           "whose hands have lovingly sharpened and oiled the blade. "+
           "The hilt is as long as the blade itself, and the pommel is "+
           "fitted with an ornament.\n");
}

void create_weapon()
{
    set_name("dagger");    
    add_name("blade");
    set_hit(13 + random(3));
    set_pen(20);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_item(({"hilt", "handle"}),
        "The hilt is as long again as the blade, and wrapped in fine "+
        "silver wire. There is an ornament on the pommel.\n");
    add_item(({"pommel", "ornament", "enamel", "symbol", "sigil"}), 
        "@@exa_pommel@@");

    configure_it();
}

string exa_pommel()
{
    string str;
    
    if (query_sigil())
    {
        str = "It is the sigil of a Sybarite House: "+ 
              query_sigil() +".\n";
    }   
    else
        str = "It appears to have been broken recently, and you "+
              "can no longer discern what it was.\n";

    return "There is a silver and enamel symbol on the pommel.\n"+ str;
}

string query_recover()
{
    return MASTER + ":" + query_wep_recover() 
                  + "#ADA#"+ad1+"#ADA#"+ad2+"#SIG#"+sigil+"#";
}

void 
init_recover(string arg)
{
    string   foo;

    init_wep_recover(arg);
    sscanf(arg, "%s#ADA#%s#ADD#%s#SIG#%s#", foo, ad1, ad2, sigil);

    configure_it();
}

