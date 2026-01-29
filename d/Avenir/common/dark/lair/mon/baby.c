// small monkey  (/d/Avenir/common/dark/mon/baby.c)
// Creator:      Casca, 12/04/99
// Updates: Lucius, Jan 2005: Changed to use /std/monster so it's attackable
//            amongst other things.  It doesn't use anything special.
// Purpose:      
// todo: 

inherit "/std/monster.c";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/deities.h"

int alarm_id;
string albus_long();

void
create_monster()
{
    set_name("baby");
    set_pname("babies");
    set_race_name("albus");
    add_name(({"albus_baby", "infant", "newborn", "baby"}));
    set_adj(({"tiny", "infant", "baby","newborn"}));
    set_short("infant albus");
    set_pshort("infant albi");
    set_long(albus_long);
    set_alignment(0);
    set_gender(random(2));

//  Sets the stats for us, its a simple npc 
    default_config_creature(8);

    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_VOLUME, 6000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(UNIVERSAL_OFFERING, 1);  
  

    set_act_time(10);
    add_act("emote scrunches up its face.");	
    add_act("emote cries loudly.");
    add_act("emote watches you with vacant eyes.");
    
    set_cact_time(10);
    add_cact("emote cries loudly.");
}

string
albus_long()
{
    string  str;
    int i;

    i = random(4);
    switch (i)
    {
        case 0: str = "This is very small, newly born albus baby. It is still covered "+
                            "with blood and mucus.\n";
        break;
        case 1: str = "A baby albus, perhaps a few hours old.\n";
        break;
        case 2: str = "An infant of the albus species. It appears to be a day or two old.\n";
        break;
        case 3: str = "A week old, two at most, this infant is of the albus species.\n";
        break;
    }

    str += "It is much too young to be seperated from its mother.\n";

    return str;
}

void
baby_die(object ob)
{
    command("emote turns blue before your very eyes.");
    ob->set_hp(-1);
    ::do_die(environment(ob));
    ob->remove_object();
}

/*
 * Function name: init_living
 * Description:   This function is called when this object encounters a 
 *                new living.
 */
void
init_living()
{
    ::init_living();

 
    /* If a player, light_cry */
    if (interactive(this_player()))
    {
        if (alarm_id)
            return;
        alarm_id =  set_alarm(120.0, 0.0, &baby_die(this_object()));
        return;
    }

    if (this_player()->id("albus"))
    {
        command("smile sweet at albus");
        remove_alarm(alarm_id);
        this_player()->command("get baby");
        return;
    }      
}

