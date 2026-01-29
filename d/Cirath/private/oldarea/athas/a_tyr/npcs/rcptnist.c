/* rcptnist.c: Person who sells keys in the Golden Inix in Tyr.
 *   Based on Merrygrin's potion_man.c
 *  If psionics code is created she will be high level, but for
 *  now her power is represented by OBJ_M_NO_*ATTACK            */

inherit "/std/monster.c";
inherit "/lib/trade";

#include "defs.h"
#include "/sys/money.h"
#include "/d/Cirath/common/introfnc.h"

#define NUM   4

void
create_monster()
{
    set_name("mila");
    set_adj("serious");
    add_adj("inquisitive");
    set_title("Risani, owner of the Golden Inix Inn");
    set_race_name("half-elf");
    set_gender(1);
    set_long("Graceful and competent, this half-elf seems to emenate a "+
             "force of will unlike any you have felt. It is almost as if "+
             "your mind was being forced to respect her. Nay, not almost, "+
             "you are convinced that is exactly what it is. Still she "+

             "seems a peaceable sort and may even let you 'rent room', "+
             "if you have exact change anyway.\n");

    default_config_npc(75);
    add_prop(OBJ_M_NO_ATTACK, "As you prepare your attack she meets your gaze, and the will to do anything leaves.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "She lets out a small smile and suddenly your mind is to clouded to function.\n");

    set_alignment(750);
    add_act("say So, what news from outside Tyr?");
    add_act("emote orders some scullery maids to do their jobs.");
    add_act("emote seems to be concentrating on something.");
    add_act("emote smiles warmly.");
    add_act("say Please don't make trouble. It could get...messy.");
    add_act("say Would you like to rent a room?");

    seq_new("hubba");
    seq_addfirst("hubba",({"@@do_give"}));

    set_act_time(6);
    MONEY_MAKE_CC(1000)->move(TO, 1);
    config_default_trade();
}

void
init_living() { add_action("do_buy", "rent"); }

do_give()
{
    object key;
    int i;

    if(environment())
    {
        for(i=0;i<10;i++)
        {
            key = clone_object(TYR_OBJECT+"roomkey.c");
            key->move(TO);
        }
    }
}

do_buy(string str)
{
    object testkey;
    int price, *result, change, i;

    if(!(str=="room"))    {
        notify_fail("She says: Rent what? A room?\n");
        return 0;    }

    testkey = present ("_tyr_room_key_", TO);

    if(!objectp(testkey))    {
        notify_fail("She says: Sorry, all my rooms are rented.\n");
        return 0;    }

    price = 144;

    result = pay(price, TP, "gold", 0, TO, "copper");
    if(sizeof(result)==1) {return 0; }

    if(testkey->move(TP))    {
        say(QCTNAME(TP)+" drops a key on the ground.\n");  }

    write("You get a key to the room you are renting.\n");
    write("You pay "+text(result[0 .. NUM -1])+".\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    seteuid(getuid(TO));

    if(change) {write("You get, " +change+ " as change.\n"); }
    
    command("say Enjoy your stay.");
    return 1;
}

query_knight_prestige() {return(-6); }
