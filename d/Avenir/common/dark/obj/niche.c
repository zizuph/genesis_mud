//-*-C++-*-
//  /d/Avenir/common/dark/niche.c
// creator(s):   Casca, 12/9/99
// last update:  Lilith. 05/20/2000
// purpose:      Niche for Sair's gem offerings
// note:
// bug(s):
// to-do:        


inherit "/std/container";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"

#define FIXEUID   setuid(); seteuid(getuid())

void prevent_enter(object ob);

/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
 *
 *    For when it is called see:
 *    /d/Avenir/smis/std/placer_mod.c
 *
 *    If it returns 1, the placer will do nothing, but if it returns 0,
 *    the placer will clone a new object.
 *
 */
public int
reset_placed_functions()
{   
    // fill the niche with a gem.
    if (sizeof(all_inventory(this_object())) < 3)
    {
        clone_object("/d/Genesis/gems/obj/opal_fire")->move(this_object(), 1);
    }
    return 1;
}

string niche_inv()
{
    object *stuff;

    stuff = FILTER_DEAD(all_inventory(TO));
    if(!sizeof(stuff))
       return "";
    else
        return " Sitting in the niche is "+ COMPOSITE_DEAD(stuff);
}

void 
create_container()
{
    set_name("niche");

    set_long("This niche was carved with care so great it would seem "+
        "almost reverent.  "+
        "The carved stone is flawless, free of chisel marks or chips, "+
        "and perfectly symmetrical in cut.  "+
        "Set at about eye-level in the wall, the niche is a hands-length "+
        "deep and two-hands in height and width.  "+
        "The bottom and top sides of the niche are flat while the walls have "+
        "five sides as if the niche was an octagon cut in half. "+
        "The surfaces of the niche and the nearby wall have been smoothed "+
        "and polished to a mirror-like surface. "+
        "The back wall of the niche is engraved engraved with a large "+
        "octagon that has been inlaid with a faintly glowing red crystal."+
        "@@niche_inv@@\n");
 
    add_prop(CONT_I_RIGID, 1);
    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    remove_prop(OBJ_I_VALUE);

    set_no_show_composite(1);

    FIXEUID;

    reset_placed_functions();
}
int
prevent_enter(object ob)
{

    if (ob->id("_sair_gem") && !this_player()->query_prop("_live_i_is"))
        return 0;

    if (this_player()->query_prop("sair_blessing") && ob->id("_sair_gem"))
    {
        write("A red glow flickers around your hand as it "+
            "breaches the plane of the niche. "+
            "As you reach further into the niche a slight "+
            "feeling of pressure moves up your hand and a tangible "+
            "energy causes your skin to tingle and hairs to stand erect.\n");
        say("As "+QTNAME(TP)+" reaches into the "+short()+" a red glow "+
            "surrounds his hand.\n");

        return 0;
        }
    else write("A shock goes through your hand and a red light flickers "+
            "across the plane of the " + short() + " as you attempt to reach "+
            "through it.\n");
        say("As "+QTNAME(TP)+" attempts to reach into the "+short()+" a "+
            "red flash erupts from it and "+PRONOUN(TP)+" jerks back "+
            POSSESS(TP)+" hand in apparent pain.\n");

        return 1;

}


int
prevent_leave(object ob)
{
    if (this_player()->query_prop("sair_blessing"))
    {
        write("A red glow flickers around your hand as it "+
            "breaches the plane of the niche. "+
            "As you reach further into the niche a slight "+
            "feeling of pressure moves up your hand and a tangible "+
            "energy causes your skin to tingle and hairs to stand erect.\n");
       say("As "+QTNAME(TP)+" reaches into the "+short()+" a red glow "+
            "surrounds his hand.\n");

        return 0;
    }
    else 
    {
        write("A shock goes through your hand and a red light flickers "+
            "across the plane of the " + short() + " as you attempt to reach "+
            "through it.\n");
        say("As "+QTNAME(TP)+" attempts to reach into the "+short()+" a "+
            "red flash erupts from it and "+PRONOUN(TP)+" jerks back "+
            POSSESS(TP)+" hand in apparent pain.\n");
    }
    return 1;
}

