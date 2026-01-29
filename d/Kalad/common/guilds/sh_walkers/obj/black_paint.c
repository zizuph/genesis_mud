inherit "/std/object";
#include "/d/Kalad/defs.h"


void
create_object()
{
    set_name("_face_paint_");
    set_long("This object is used to aid someone in their hide "+
    "ability.\n");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    set_no_show();
}


void
init()
{
    ::init();
    AA(do_rub,rub);
}

string 
show_subloc(string subloc,object on, object for_ob)
{
    string str,str2;
    if(subloc != file_name(TO))
        return "";
    if(on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if(on == for_ob)
    {
        str = "You have";
        str2 = "your";
    }
    else
    {
        str = HE(TP)+" has";
        str2 = HIS(TP);
    }
    str = str+" some black paint smeared on "+str2+" face.\n";
    return str;
}

int
do_rub(string str)
{
    NF("Rub what?\n");
    if(str != "paint off face")
        return 0;
    write("You rub the black paint off your face.\n");
    say(QCTNAME(TP)+" rubs the black paint off "+HIS(TP)+" face.\n");
    remove_object();
    return 1;
}

void
enter_env(object to, object from)
{
    int skval;
    if(to)
        if(living(to))
        {
            to->add_prop("_kalad_has_black_paint",1);
            skval = to->query_skill_extra(SS_HIDE);
            skval = skval+2;
            to->set_skill_extra(SS_HIDE,skval);
            to->add_subloc(file_name(TO),TO);
        }
    ::enter_env(to,from);
}

void
remove_object()
{
    E(TO)->set_skill_extra(SS_HIDE,E(TO)->query_skill_extra(SS_HIDE) - 2);
    E(TO)->remove_prop("_kalad_has_black_paint");
    E(TO)->remove_subloc(file_name(TO));
    ::remove_object();
}
