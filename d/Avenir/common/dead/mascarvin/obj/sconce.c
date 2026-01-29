inherit "/std/container";
#include "../defs.h"

#define TORCHFILE   (TOBJ + "ivory_torch")

object
*torches()
{
    return filter(all_inventory(TO), &->id("torch"));
}

object
my_torch()
{
    object *mine = torches(), *lit;

    if(!sizeof(mine))
       return 0;

    lit = filter(mine, &->query_prop(OBJ_I_HAS_FIRE));

    if(sizeof(lit))
       return lit[0];
    else
       return mine[0];    
}

void
torch_msg()
{
    if(!my_torch())
        return;

    tell_room(ENV(TO), CAP(LANG_ASHORT(my_torch()))
          + " flares to life in " + LANG_THESHORT(TO) + ".\n");
}

void
reset_container()
{
    object torch;

    if(!my_torch())
    {
       if(ENV(TO))
          all_inventory(TO)->move(ENV(TO));

       seteuid(getuid());
       torch = clone_object(TORCHFILE);
       torch->light_me();
       torch->move(TO, 1);

       set_alarm(1.0, 0.0, torch_msg);
    }
}

nomask void
create_container()
{
    if(!IS_CLONE)
        return;

    set_name("sconce");
    set_short("wrought-iron sconce");
    add_name(({"stand","bracket", "torchstand", "iron", "wrought", "wrought-iron"}));
    set_adj(({"torch", "iron"}));
    set_long("It is an intricate sconce, made from wrought iron "
      + "formed in weaving designs. ");

    add_prop(OBJ_M_NO_GET, "It is firmly secured to the wall.\n");

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 11000);
    add_prop(CONT_I_MAX_VOLUME, 11000);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);

    set_no_show_composite(1);

    reset_container();
}

string
external_desc()
{
    object torch = my_torch();
    string str;

    str = "Fastened to the wall is a large, intricate iron "
        + "sconce";

    if(torch)
      str += ", within which " + LANG_ASHORT(torch) + " flickers and "
        + "burns";

    return str + ".";
}
