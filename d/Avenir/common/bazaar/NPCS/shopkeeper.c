// file name:	shopkeeper.c
// creator(s):	Ilyian
// last update:	Denis, May'97
// purpose:	Shopkeeper
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/common/bazaar/bazaar.h"
# include <money.h>

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

int armed;

void
create_monster()
{
    set_name("maria");
    set_adj(({"slender", "bright-eyed"}));
    set_title("Oplune, Proprietor of the Bazaar Goods and Services");
    set_living_name("maria");
    add_name(({"shopkeeper","keeper"}));
    set_race_name("human");
    set_gender(1);

    set_long("This tall woman is in charge of keeping " +
             "the shop and turning a profit.\n");

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);

    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(100);
    set_knight_prestige(-2);

    set_chat_time(52);
    add_chat("Greetings, stranger!");
    add_chat("Welcome to my shop!");
    add_chat("Lets get down to business.");

    set_cchat_time(3);
    add_cchat("Get outta here!");
    add_cchat("Attacking poor defenseless women, sheesh!");
    add_cchat("Shame on you!");

    set_cact_time(1);
    add_cact("slap enemy");
    add_cact("scream");
}

public void
arm_me()
{
    seteuid(getuid());
    MONEY_MAKE_SC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
}

static void
react_attack()
{
    command("say Hmph...let me get ready..");
    TO->move_living("up",INTR + "store",0,0);
    command("get weapon");
    command("get armour");
    command("remove all");
    command("wear all");
    TO->move_living("down",INTR + "shop",0,0);
    command("wield all");
    command("grin danger");
    armed=1;
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (!armed)
        react_attack();
}

public string
race_sound()
{
    return "whispers";
}

