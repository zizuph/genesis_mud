
/* 
   Ahoy, used to shout to / from boats in the area,
   taken from shout in soul_cmd.

   Adapted by Maniac April 96.
 */ 

#include <language.h> 
#include <options.h>


object *
query_boat_rooms_linked(object ar)
{
    object l, *b, *r;
    int i;

    r = ({ }); 

    if (ar->query_inside_of_boat()) {  
        ar = ar->query_boat_loc();  
        r = ({ ar }); 
    } 

    if (!objectp(ar))
        return ({ });

    b = ar->query_boats();  

    for (i = 0; i < sizeof(b); i++) 
        if (objectp(l = b[i]->query_boat_in())) 
            r += ({l}); 

    return r; 
}


int
ahoy(string what)
{
    object *rooms;
    object troom;
    int    index;
    int    size;

    if (!this_player())
        return 0;

    if (!what)
    {
        notify_fail("Ahoy what?\n");
        return 0;
    }

    if (!(troom = environment(this_player())))
        return 0;

    rooms = ({troom}) + query_boat_rooms_linked(troom); 

    index = -1;
    size = sizeof(rooms);
    while(++index < size)
    {
        tell_room(rooms[index], "@@ahoy_name:" + file_name(this_object()) +
            "@@ ahoys: " + what + "\n", this_player());
    }

    if (this_player()->query_option(OPT_ECHO))
        write("You ahoy: " + what + "\n");
    else
        write("Ok.\n");
    return 1;
}


string
ahoy_name()
{
    object pobj;
    string str;

    pobj = previous_object(); /* Reciever of message */
    if (file_name(pobj) == "/secure/vbfc_object")
        pobj = previous_object(-1);
    if (pobj->query_met(this_player()))
        return this_player()->query_name();
    else
    {
        if (environment(pobj) == environment(this_player()))
            str = this_player()->query_nonmet_name();
        else
            str = this_player()->query_gender_string() + " " +
                this_player()->query_race_name() + " voice";
        return capitalize(LANG_ADDART(str));
    }
}

