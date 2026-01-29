// file name: crypt_key.c
// creator(s): Ilyian, Oct 15, 1995
// last update:
// purpose: Key to the gate of the crypts. It is held
//          by the banshee.
// note:
// bug(s):
// to-do:

inherit "/std/key";
#include "../dead.h"
#include "/sys/stdproperties.h"

create_key() {
    ::create_key();

    set_name("key");
    set_adj(({"strangly", "strange", "strangely-shaped", "shaped"})); 
    set_short("strangly shaped key");
    set_long("This key is like none you have ever seen before. "
            +"It is made from fused bones, and has a very "
            +"long shaft ending in a razor sharp point. A carving " +
            "of a skeletal hand with an eye in its palm decorates the key.\n");

    set_key("_avenir_cryptmain_gate_key");
    add_prop(OBJ_I_WEIGHT, 160);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 20);

}
