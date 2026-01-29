inherit "/d/Cirath/std/monster.c";
inherit "/lib/trade";

#include "../defs.h"
#include "/sys/money.h"

#define NUM   4

void
create_monster()
{
    set_name("lorian");
    set_adj("bald");
    add_adj("black-bearded");
    set_title("the boot maker");
    set_race_name("dwarf");
    set_gender(0);
    set_long("Hard working and with a keen eye for detail, Lorian is" +
        " one of the best boot makers in whole of Athas. When he can" +
        " get the materials he wants he makes some real masterpieces." +
        " But boots is the only thing he is interested in. And even" +
        " then, only the boots he makes.\n");

    default_config_npc(75);
    add_prop(OBJ_M_NO_ATTACK, "As you are about to attack you realize the importance of a good pair of boots.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "As you are about to attack you realize the importance of a good pair of boots.\n");

    set_alignment(750);
    add_act("say You should really take better care of you boots.");
    add_act("say You nead a good pair of boots in the desert.");
    add_act("emote works with a steady hand on a new sole.");
    add_act("emote smiles warmly.");
    add_act("say Some plants have thorns hidden just under the sand. really painful if barefooted");
    add_act("say Nothing like the smell of shoe leather in the morning.");
    add_act("say What a fool. Said he wanted only one boot. I make pairs. So what" +
        " if he got a wooden leg. Thats not my problem. I sell pairs. Ack!");
    add_act("say Damned that carpenter. Who ever heard of wooden shoes. Stealing" +
        " my business he is. That bastard!");
    add_ask(({"room", "rent", "rent room"}), "Ahh..you want to rent a" +
        " room. Then you in luck my friend. When the Inn gets full I rent" +
        " out this room upstairs. You can find the stairs in the alley." +
        " One gold for the key if want to 'rent' it.\n");
    add_ask(({"favor","help","task"}),"Hehe.. I don't think I want" +
        " any new apprentice just now. If you want work check with" +
        " the caravan office or the guard barracks.\n");
    add_ask(({"boots", "shoes"}),"I have dedicated my whole life to making" +
        " the perfect pair of boots. I have come close a few times but I" +
        " will never give up. To me no craft if finer than bootmaking.\n");

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
            key = clone_object(ALT_OBJ+"roomkey.c");
            key->move(TO);
        }
    }
}

do_buy(string str)
{
    object testkey;
    int price, *result, change, i;

    if(!(str=="room"))    {
        notify_fail("He says: Rent what? A room?\n");
        return 0;    }

    testkey = present ("_altaruk_room_key_", TO);

    if(!objectp(testkey))    {
        notify_fail("He says: Sorry, all my rooms are rented.\n");
        return 0;    }

    price = 144;

    result = pay(price, this_player(), "gold", 0, TO, "copper");
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
