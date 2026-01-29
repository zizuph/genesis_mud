// Emarus the Tailor
// creator(s):	Lilith, Aug 1997
// last update:	
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "/d/Avenir/common/bazaar/bazaar.h"
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
# include "/d/Avenir/include/guilds.h"

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

void
create_monster()
{
    set_name("emarus");
    set_title("icu Wer'a, Tailor of Sybarus");
    add_name(({"shopkeeper","keeper", "tailor"}));
    set_race_name("gnome");
    set_gender(0);

    add_adj(({"bent", "old"}));
    set_long("An old gnome, bent with age and from hours stooped over "+       
         "his cutting table.\nHis eyes are kind and smiling.\n");
    set_act_time(10);
    add_act("emote scratches himself thoughtfully.");
    add_act("bow");
    add_act("wiggle slowly");
    add_act("squirm tired");
    add_act("flex slight");
    add_act("re-arranges some bolts of cloth.");

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(0);
    set_knight_prestige(-1);

    set_mm_in("arrives.");
}

public void
arm_me()
{
    object cloak, shirt, pants;

    seteuid(geteuid(this_object()));
    MONEY_MAKE_SC(random(20))->move(this_object());

    cloak = clone_object(BAZAAR + "Obj/worn/mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    shirt = clone_object(BAZAAR + "Obj/worn/menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    pants = clone_object(BAZAAR + "Obj/worn/menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    command("wear all");
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(6);

    if (!present(tp, environment(TO)))
        return;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 0)           
            command("grovel to "+ tp->query_real_name());
        else 
        if (i == 2)
            command("bow deep "+ tp->query_real_name());
        else
        if (i == 4)
            command("say to "+ tp->query_real_name() +" I am "+
                "honoured by your patronage!");
        else
        if (i == 5)
            command("say to "+ tp->query_real_name() +" May I make "+
                "you something? A cloak perhaps?");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i == 0)
            command("smile respect "+ tp->query_real_name());
        else
        if (i == 4)
            command("dance "+ tp->query_real_name());
        return;
    }       
    else
    {
        if (i == 3)
           command("say Hello! Are you here to be fitted for "+
               "some new clothes?");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  


