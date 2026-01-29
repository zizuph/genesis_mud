#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("sarul");
    set_living_name("sarul");
    set_race_name("minotaur");
    set_title("the Blacksmith of Nethosak");
    set_short("musclebound dark-haired minotaur");
    set_long("This minotaur is dressed in thick leather hides "+
             "to protect him from the immense heat from the "+
             "hot iron. He's constantly hammering at a piece of "+
             "metal, trying to form it into a weapon. This must "+
             "be one of the many smiths that have been ordered to "+
             "make armours for the Imperial Army. His forehead and "+
             "thick arms are drenched in sweat.\n");
    
    set_stats(({140,80,158,80,60,100}));
    set_alignment(random(50)-25);
    set_gender("G_MALE");

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000); 
    add_name("smith");
    add_name("blacksmith");
    set_introduce(1);
    set_default_answer("The noise of metal clanging drowns out your words.\n");
    add_ask(" [about] 'fix'", "emote points to the sign.", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    clone_object(MWEP + "hammer.c")->move(this_object(),1);
    command("wield all");
}