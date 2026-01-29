/* Ashlar, 26 Jun 97
   Slave that gives a quest
*/

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void
create_krynn_monster()
{
    int i;	

	set_name("slave");
    add_name("neraka_slave");
    set_race_name("human");
    set_adj("defiant");
    add_adj("human");
    set_short("defiant human slave");
    set_long("This slave is chained to the wall by sturdy-looking " +
        "chains.\n");

    set_stats(({45,30,40,35,35,40}));
    set_skill(SS_DEFENCE, random(25) + 5);  /* 5-29 */
    set_skill(SS_WEP_KNIFE, random(25) + 5);

    i = query_average_stat();
    set_alignment(i*(i+20));
    set_knight_prestige(-i);

    set_all_attack_unarmed(15,20);

    add_prop(LIVE_S_EXTRA_SHORT, " chained to the wall");

    set_default_answer(QCTNAME(TO) + " whispers: I know nothing about that.\n");
    /* we're using the Krynn version of asking */
    add_ask(({"quest","task","assignment","escape"}), "give_quest", 2);

}

void
qt1(string h, int n)
{
    switch(n)
    {
        case 1:
            command("whisper to " + h + " Aye, we could use your help.");
            break;
        case 2:
            command("whisper to " + h + " We need someone to fetch a few " +
                "things from the city.");
            break;
        case 3:
            command("whisper to " + h + " The owner of the Black Ship has " +
                "promised us a pack of rations.");
            break;
        case 4:
            command("whisper to " + h + " Buzlik the potion merchant agreed " +
                "to brew up something to help us.");
            break;
        case 5:
            //command("whisper to " + h + " 
            command(h + "Give me their names and evidence of their guilt, " +
                "and you shall be rewarded.");
            break;
        default:
            return;
    }
    set_alarm(1.5,0.0,&qt1(h,n+1));
}
    
string
give_quest(object tp)
{
    string h;

    h = tp->query_real_name();

    set_alarm(1.0,0.0,&qt1(h,1));

    return "smile thank";
}

void
arm_me()
{
    seteuid(getuid());
    clone_object(NARM + "rags")->move(TO);

    command("wear all");
    command("wield all");
}

