/* 
 * hawk
 *
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

/*
 * LK: Why is the purpose of this define?
 */
#define hawk           this_npc

inherit FAERUN_NPC_BASE;

#define TYPE    ({"reserved", "observant", "clever", "magical", \
    "quiet"})

#define PHYS    ({"large", "feathered", "blue-eyed", \
    "sharp-clawed", "huge-wingspan", "sharp-beaked"})

void create_monster()
string race_sound() { return "screeches"; }

{
    string type, phys;
    int i;

    /* LK: These two lines aren't necessary in most things.
     */
    seteuid(getuid());
    if (!IS_CLONE) 
        return;

    /* LK: ONF_OF_LIST is an obsolete macro, do not use it.
     *     just do 'one_of_list(TYPE);' instead.
     */
    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

    /* LK: Don't remove this prop unless you are going to
     *     code routines that require handing it things.
     *     This is a player abuse issue.
     */
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    /* LK: Where does this come from and why is it set?
     */ 
    npc_name = "_hawk_npc";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("hawk");

    set_short(type + " " + phys + " beautiful hawk");
    /* LK: Just use "short()" instead of query_short(). However,
     *     since you want an article, do this instead: "LANG_ADDART(short())".
     *     You will need to make sure that you add "#include <language.h>" to
     *     the top of the file.
     *
     *     The grammar issues can be gone over later.
     */
    set_long("This is a " + query_short() + ". He appears larger than " +
        "the average hawk, his eyes are piercing and clever. He gives " +
        "you the feeling he knows more than he lets on.\n");

    set_act_time(15);
    set_cact_time(15);
    add_act("emote stretches his wings languidly.");
    add_act("emote nuzzles his beak into his feathers");
    add_act("emote lifts his head to the sky");
    add_act("emote watches you with scrutiny");
    add_act("emote tucks his head in his feathers and falls to sleep");

    add_chat("One may smile, and smile, and be a villian.");
    add_chat("There is nothing either good nor bad, but thinking makes it so");
	add_chat("I must be cruel only to be kind; thus bad begins, and worse " +
	    "remains behind.\n") 

    add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(NPC_I_NO_LOOKS, 1);
}

/* LK: I assume you will be expanding to add commands?
 *     If not, masking this function serves no purpose.
 */
void
init_living()
{
    ::init_living();
    ::init_team_pickup();
}
