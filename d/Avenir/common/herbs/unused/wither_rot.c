// file name:    /d/Avenir/common/herbs/wither_rot.c
// creator(s):   Casca 12/18/99
// last update:  
// purpose:      Herb for the dark that causes unprotected herbs in the
//               area to wither.
// note:         Used by the Albi to wither mikkitna herbs used in their cavern.
//               Many thanks to Shiva for his assistance (for writing I mean)
//               the function.
// bug(s):
// to-do:

inherit "/std/herb";
#include <files.h>
#include <macros.h>
#include "/sys/herb.h"
#include <stdproperties.h>
#include "/d/Avenir/common/common.h"

void destroy_herbs(object *obs);

create_herb()
{
    set_name("pod");
    add_name("herb");
    add_pname(({"pods","herbs"}));
    set_short("grey spore pod");
    set_herb_name("wither-rot");
    set_adj("grey");
    add_adj("spore");
    set_id_long("This is a small transparent pod which holds thousands of "+
        "microscopic grey spores. "+
        "The spores are known simply 'Wither-rot' due to it effect on "+
        "other plant matter that it come in contact with.\n");
    set_unid_long("This is a small transparent pod which holds thousands of "+
        "microscopic grey spores.\n");
    set_ingest_verb("smash");
    set_id_diff(30);
    set_find_diff(3);
    set_effect(HERB_SPECIAL,"",0);
    set_decay_time(200);
    set_herb_value(450);

}

void special_effect()
{
    setuid(); seteuid(getuid());

    tell_room(environment(this_player()),
	"The " + short() + " explodes in a grey cloud...\n"+
        "The cloud causes all the plant matter it comes in contact "+
        "with to wither and rot away.\n");

    //destroy_herbs not called in usual manner cause the action of smashing
    //the herb destroys it preventing the routine from running through.
    MASTER->destroy_herbs(({ environment(this_player()) }));

}

public int
find_herbs(object ob)
{
    return IS_HERB_OBJECT(ob);

}

public int
find_containers(object ob)
{
    return (IS_CONTAINER_OBJECT(ob) &&
        (!ob->query_prop(CONT_I_CLOSED) || ob->query_prop(CONT_I_ATTACH)));
}
    
/*
 * Function name: destroy_herbs
 * Description:   Recursively destroy herbs
 * Arguments:     object *obs - the containers in which to look for herbs.
 */
public void
destroy_herbs(object *obs)
{
    int i;
    object *all, *herbs, *conts = ({});

    obs -= ({ 0 });
    for (i = 0; i < sizeof(obs); i++)
    {
        all = all_inventory(obs[i]);
        herbs = filter(all, find_herbs);
        conts += filter(all, find_containers);

        herbs->remove_object();
	if (sizeof(herbs) > 0)
        clone_object(HERB + "powder")->move(obs[i], 1);
    }

    if (sizeof(conts))
    {
        // The alarm is very important to avoid eval cost errors.  By
        // means should it be replaced by an immediate call.
        set_alarm(1.0, 0.0, &destroy_herbs(conts));
    }
}

