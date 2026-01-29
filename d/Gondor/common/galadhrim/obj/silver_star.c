#pragma strict_types

#include <stdproperties.h>
#include "../
inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

void
create_object()
{
     set_name("star");
     add_adj(({"small", "silver"}));
     set_long("It is a small eight-pointed star made of silver. At least " +
	      "you think it is silver. There must be some kind of " +
	      "enchantment cast on the star, for when you touch it, it " +
	      "gleams with a pale white light.\n");
     add_prop(OBJ_I_WEIGHT, 180);
     add_prop(OBJ_I_VOLUME, 25);
     
     add_spell("/d/Genesis/magic/spells/identify");
 }

void
enter_env(object env, object from)
 {
     ::enter_env(env, from);
     add_spell_object(env);
 }

 void
 leave_env(object env, object to)
 {
     ::leave_env(env, to);
     remove_spell_object(env);
 }
 
