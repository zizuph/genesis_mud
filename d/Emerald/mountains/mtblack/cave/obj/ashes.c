/* A pile of ashes, containing torches -  recoded by Tulix III, 07/08/95 */
 
inherit "/std/container";
#include "/d/Emerald/defs.h"
 
/* Prototype functions */
void reset_container();
string my_get();

void
create_container()
{
    set_name("ash");
    set_pname("ashes");
    add_name("pile");
    add_name("remains");
    set_short("pile of ashes");
 
    set_long("Its a pile of ashes, still glowing red. A pile of ashes " +
             "this big suggests that it was quite a large fire. You notice " +
             "that you could probably go down through the ashes.\n");

    add_prop(OBJ_M_NO_GET, "@@my_get"); /* No-one can pick it up */
    add_prop(CONT_I_WEIGHT, 2000);      /* ashes weigh 2kg       */
    add_prop(CONT_I_MAX_WEIGHT, 5000);  /* can hold up to 3kg    */
    add_prop(CONT_I_VOLUME, 5000);      /* takes up 5 litres     */
    add_prop(CONT_I_MAX_VOLUME, 12000); /* can hold up to 7l     */
    
    set_alarm( 1.0, 0.0, reset_container);
}

string
my_get()
{
    tell_room( ENV(TO), QCTNAME( TP ) + " burns his fingers while trying " +
          "to pick up the hot ashes.\n", TP);

    return("Ouch! You burn your fingers trying to pick up some of the hot " +
           "ashes. You decide it was not such a smart move after all.\n");
}

void
reset_container()
{
    object torch;
 
    seteuid(getuid());
    
    torch=present("torch");
    if (!torch)
    {
        torch=clone_object( CAVE_DIR + "obj/small_torch");
        torch->move( TO );
    
        torch=clone_object( CAVE_DIR + "obj/small_torch");
        torch->move( TO );
    }
}
