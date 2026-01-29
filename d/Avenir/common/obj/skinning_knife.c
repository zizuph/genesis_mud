// /d/Avenir/common/obj/skinning_knife
// creator(s):   Achdram & Lilith
// last update:  Nov 2004
// purpose:      skinning corpses for the tanner to turn into leather goods
// note:	
// bug(s):
// to-do:        
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";

#include "/d/Avenir/include/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>           
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define CORPSE_I_SKINNED "_corpse_i_skinned"

/* define this once the object is created */
#define AV_SKIN   "/d/Avenir/common/obj/skin"

void 
create_weapon ()
{
    set_name("knife");
    set_adj(({"skinning", "sharp"}));
    set_short("sharp skinning knife");
    set_long("This knife is very sharp.  It has a moon "+
        "blade with sharp edges for removing the skins "+
        "from corpses.\n");
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hit(10);
    set_pen(15);
    set_hands(W_ANYH);     

    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,15) + random(50) - 20);

}


/*
 * Function name: f_corpse
 * Description  : Support function for skin command.
 * Arguments    : object ob - the object to check.
 * Returns      : int 1/0 - if true, it's a suitable corpse.
 */
public int
f_corpse(object ob)
{
    if (IS_CORPSE_OBJECT(ob) &&
	((environment(ob) == this_player()) ||
	 (environment(ob) == environment(this_player()))))
    {
	return 1;
    }

    return 0;
}

/*
 * Function name: get_skin
 * Description:   Get skin from the corpse
 * Arguments:     string arg - command-line argument.
 * Returns:       int 1/0 - success/failure.
 */
public int
get_skin(string arg)
{
    mixed	corpses, skins;
    object 	*found, target, myskin;

    if (this_player()->query_prop(TEMP_STDCORPSE_CHECKED))
	return 0;

  
    notify_fail("Skin the what?\n");  /* access failure */
    if (!arg)
	return 0;

    if (!parse_command(arg, environment(this_player()), "[the] %i",
		corpses))
	return 0;

    found = VISIBLE_ACCESS(corpses, "f_corpse", this_object());
    
    if (sizeof(found) != 1)
    {
        set_alarm(0.5, 0.0, &(this_player())->remove_prop(TEMP_STDCORPSE_CHECKED));
        this_player()->add_prop(TEMP_STDCORPSE_CHECKED, 1);
        if (sizeof(found))
	    notify_fail("Which corpse? Be more specific.\n");
        else
	    notify_fail("There is no such corpse nearby.\n");
        return 0;
    }
    target = found[0];
    if (target->query_prop(CORPSE_I_SKINNED))
    {
        notify_fail("That corpse has already been skinned.\n");
        return 0;
    }

    /* We aren;t using the skin leftover, and we don't want
     * players seeing a skin after we've supposedly removed it.
     */
    if (target->query_leftover("skin"))
        target->remove_leftover("skin");

    target->add_prop(CORPSE_I_SKINNED, 1);

    setuid();
    seteuid(getuid());
    myskin = clone_object(AV_SKIN);
    myskin->set_skin_race(target->query_prop(CORPSE_S_RACE));
    myskin->init_the_skin();
    myskin->move(this_player(), 0);

    say(QCTNAME(this_player()) + " skins " + QSHORT(target) + ".\n");
    write("You skin the corpse.\n");
    return 1;
}

/*
 * Function name: init
 * Description  : Called to link the tear/cut commands to the player.
 */
void
init()
{
    ::init();

    add_action(get_skin, "skin");
}
