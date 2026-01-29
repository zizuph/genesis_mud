
// Albus' (pale near-albino goblinoid creatures in the underdark)
// creator(s): Casca, 11/26/99
// purpose:    Populate the underdark
// note:       
// bug(s):     Lilith Oct 2014: change polearm skill to 90 instead of 900
// to-do:      

inherit "/d/Avenir/inherit/monster.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/trigaction";

#include "/d/Avenir/common/common.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>
#include "/d/Genesis/gems/gem.h"
#include <tasks.h>

#define FIXEUID   setuid(); seteuid(getuid())

void equip_me();


void
create_monster()
{

    ::create_monster();

    set_name("massive red-eyed albus");
    set_pname("massive red-eyed albus'");
    add_name(({"odd-one"}));
    set_race_name("albus");
    set_gender(G_MALE);
    set_adj(({"massive","red-eyed"}));
    set_short("massive red-eyed albus");
    set_pshort("massive red-eyed albus'");
    set_long("This albus is huge... he is twice as tall as any other "+
        "albus you have ever seen. He also lacks the hunched stature. "+
        "He is a true albino with long yellowish-white hair. "+
        "His eyes are a milky red which seem to burn with an inner fire."+
        "\n");
   
/*              str, con, dex, int, wis, dis           */
    set_stats(({120, 100, 100,  70,  70,  80}));

    set_alignment(0);
 
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS, 80); 
    set_skill(SS_BLIND_COMBAT, 80 );
    set_skill(SS_PARRY, 75 );


    NEVERKNOWN;

        set_act_time(7 + random (6));
    add_act("grin evilly");
    add_act("growl .");
    add_act("yawn");
    add_act("stretch");
    add_act("emote paces back and forth.");
    add_act("peer curiously goblin");
    add_act("point human");
    add_act("say What do you want here?");
    add_act("say We do not like your kind, please leave.");
    add_act("twirl staff");


        set_cact_time(9 + random (20));
    add_cact("snicker");
    add_cact("spit enemy");
    add_cact("scream");
    add_cact("cackle .");
    add_cact("glare angr enemy"); 
    add_cact("twirl staff");

    add_ask(({"odd-one","Odd_one","oddone","Oddone","odd one","Odd one",
        "leader","massive red-eyed albus", "massive albus"}),
        "say That would be me, the others call me that because I am so "+
        "different from them..", 1);
    add_ask(({"cavern", "home"}),
        "say This cavern allows us to have a safe home for once. "+
        "No more running and hiding from the ogres. If the do find us "+
        "we will fight them.", 1);
    add_ask(({"trash","tunnel","junk"}),
        "say We make use of what we can.", 1);
    add_ask(({"miners","trolls","foreman","foremen","shadow-elves"}),
        "say We use things they no longer want, good tools for "+
        "for breaking rocks and food they dont need.", 1);

}

void
equip_me()
{
    object staff, gem;
    FIXEUID;

    gem = RANDOM_GEM_BY_RARITY(GEM_RARE);
    gem->move(this_object());    

    staff = clone_object(DARK + "/obj/cstaff");
    staff->move(TO);

    command("wear all");
    command("wield all");
}

public void
add_introduced(string name)
{
    command("nod though");
}
