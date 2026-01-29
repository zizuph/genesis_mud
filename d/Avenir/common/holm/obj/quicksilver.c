// file name:   /d/Avenir/common/holm/obj/quicksilver.c
// creator(s):  Lilith, June 1998
// revision(s): 
// purpose:     Quest obj: Material that bazaar armourer needs. 
// note:        
// bug(s):           
// to-do: 

inherit  "/std/object";

void
create_object()
{
    set_name("pool");
    add_name(({"metal", "silver"})); 
    add_name("_Aclolthayrs_gift_for_smith");
    set_adj(({"gleaming", "silver"}));
 
    set_short("pool of gleaming silver");
    set_long("This is a circular sheet of a silvery metal which, "+
        "oddly enough, looks like it was once a pool of liquid. It "+
        "seems to ripple before your eyes, distorting the images "+
        "that its mirror-like surface reflects.\n");
}

