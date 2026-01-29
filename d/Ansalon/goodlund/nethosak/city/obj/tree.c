inherit "/std/object";
#include "/sys/stdproperties.h"

string face();

void create_object()
{
    set_name("tree");
    add_name("oak");
    set_adj("tall"); 
    add_adj(face()); 
    set_long("This is a tall oak tree.\n");
    set_short("tall " +face()+ " oak tree");    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VALUE, 0);
}

string
face()
{
    // Set description.
    string *faces;
    faces = ({"green", "brown", "ancient", "young", "old"});
    return faces[random(sizeof(faces))];
}

