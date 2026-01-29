/* Fine cloth.
   Object for the spear tour on Mounty Kyrus. 
   Found in the hardware store in the Palace.

   Coded by Maniac.

   History:
            21/5/95       Created                 Maniac
*/

#include <stdproperties.h>
#include <macros.h>
#include "obj.h"
#include SPEAR_QUEST

inherit "/std/object";

mapping polished = ([ ]);


void
create_object()
{
    set_name("cloth");
    add_name(SQ_POLISH_OB); 
    set_adj("fine");      
    set_short("fine cloth");
    set_pshort("fine cloths");
    set_long("A piece of very fine cloth that would seem appropriate " +
             "for polishing metals.\n");
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 50);
}


void
remove_object()
{
   object ob = environment(this_object());

   if (interactive(ob))
       ob->catch_msg("The " + short() + " disappears.\n");

   ::remove_object();
}


int
polished_all_spears(object tp)
{
    mixed bronze, silver, golden, steel, mithril, crystalline;
    string nm = tp->query_name();

    bronze = polished["bronze"];
    silver = polished["silver"];
    golden = polished["golden"];
    steel = polished["steel"];
    mithril = polished["mithril"];
    crystalline = polished["crystalline"];

    if (bronze && silver && golden && 
        steel && mithril && crystalline) 
        if ((member_array(nm, bronze) > -1) &&
            (member_array(nm, silver) > -1) &&
            (member_array(nm, golden) > -1) &&
            (member_array(nm, steel) > -1) &&
            (member_array(nm, mithril) > -1) &&
            (member_array(nm, crystalline) > -1)) 
            return 1;
    return 0;    
}


void
quest_check(object tp)
{
    if (polished_all_spears(tp)) {
        tp->catch_msg("An apparition of Krom the Calian guildmaster " +
                      "appears to you.\nHe tells you: Thank you!\n" +
                      "The figure then disappears again.\n");
                     
        if (tp->test_bit(SQ_DOM, SQ_GROUP, SQ_BIT))  {
            set_alarm(1.0, 0.0, "remove_object");
            return;
        }
        
        seteuid(getuid());
        tp->add_exp(SQ_XP);  
        tp->catch_msg("You feel a little more experienced.\n");
        tp->set_bit(SQ_GROUP, SQ_BIT);
        tp->command("save");
        log_file("spear_tour", tp->query_name() + " " + ctime(time()) + 
                 ".\n");
        set_alarm(1.0, 0.0, "remove_object");
    }
}


void
polish_msg(object tp, string sd)
{
    tell_room(environment(tp), QCTNAME(tp) + " polishes the " +
              sd + " spears to a bright shine with the " + short() +
              ".\n", tp);
    tp->catch_msg("You polish the " + sd + " spears to a bright " +
                  "shine with the " + short() + ".\n");
}


void
do_polish(object tp, string sd)
{
    object e;
    string nm;
    string *names;

    tp = this_player();
    nm = tp->query_name();
    e = environment(tp);

    if (!(e->query_spear_quest_type() == sd))
        return;

    if (!polished[sd]) {
        polish_msg(tp, sd);
        polished += ([sd : ({nm})]);
        quest_check(tp);
        return;
    }

    names = polished[sd];
    if (member_array(nm, names) == -1) {
        polish_msg(tp, sd); 
        polished = m_delete(polished, sd);
        names += ({nm});
        polished += ([sd : names]); 
        quest_check(tp);
        return;
    }
    
    polish_msg(tp, sd);
}

