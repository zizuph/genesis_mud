#pragma save_binary

/* A file to be included into room tell rooms to switch off the
   alarm immediately when there are no more interactives here.

   Coded by Maniac, 19/9/95
*/

int interactive_count;

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        interactive_count++;
    if (interactive_count == 1)
        start_room_tells();
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (interactive(ob))
        interactive_count--;
    if (interactive_count == 0)
        stop_room_tells();
}
