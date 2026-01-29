


/*  Function name: do_throw
    Description: 

*/
int
do_throw(string str)
{
    object tp = this_player();

    if (!str)
    {
        notify_fail("Throw what?\n");
        return 0;
    }

    object * ob = FIND_STR_IN_OBJECT(str, tp);
    object * ob2 = FIND_STR_IN_OBJECT(str, environment(tp));
    if (sizeof(ob) > 0 || sizeof(ob2) > 0)
    {
        object roomExists = query_master_instance_pointer()->query_rooms(x, y, z+1);

        if (roomExists != 0)
        {
            if (!query_tied() || (query_tied() && str != "rope"))
            {
                tp->catch_msg("You throw " + str + " down the hole.\n");
                tell_room(environment(tp), QCTNAME(tp) + " throws " + str + " down the hole.\n", tp);

                if (sizeof(ob) > 0)
                {
                    ob[0]->move(roomExists);
                }

                if (sizeof(ob2) > 0)
                {
                    ob2[0]->move(roomExists);
                }

                tell_room(roomExists, str + " comes flying from the hole above and lands on the ground.\n", tp);
            }
            
            if (query_tied() && str == "rope")
            {
                if (!query_thrown_rope())
                {
                    tp->catch_msg("You throw the tied rope down the hole.\n");
                    tell_room(environment(tp), QCTNAME(tp) + " throws the tied rope down the hole.\n", tp);

                    tell_room(roomExists, "A rope comes flying from the hole above, it now dangles freely.\n", tp);

                    roomExists->add_exit(file_name(this_object()), "up");

                    roomExists->remove_item("roof" );
                    roomExists->add_item(({ "roof" }),
                        "There's a hole in the roof and a rope dangling from above.\n");

                    thrown_rope = 1;
                }
                else
                {
                    tp->catch_msg("The rope tied here is already dangling down the hole.\n");
                }
            }
            
            if (!query_tied() && str == "rope")
            {
                tp->catch_msg("Perhaps you should tie the rope to a rock first.\n");
            }
        }
    }
    else
    {
        notify_fail("You have no " + str + ".\n");
        return 0;
    }
    return 1;
}

/*  Function name: do_pull
    Description: 

*/
int
do_pull(string str)
{
    object tp = this_player();

    if (!str)
    {
        notify_fail("Pull what?\n");
        return 0;
    }

    if (query_thrown_rope() && str == "rope")
    {

        tp->catch_msg("You pull the tied rope from the hole.\n");
        tell_room(environment(tp), QCTNAME(tp) + " pulls the tied rope from the hole.\n", tp);

        object roomExists = query_master_instance_pointer()->query_rooms(x, y, z+1);

        roomExists->remove_exit("up");

        roomExists->remove_item("roof" );
        roomExists->add_item(({ "roof" }),
            "There's a hole in the roof.\n");

        tell_room(roomExists, "The rope is being pulled from above you, you could say you're stranded now.\n", tp);

        thrown_rope = 0;

        return 1;        
    }
    return 0;    
}


int
tie_object(object rope, string where)
{
    object tp = this_player();

    if (where != "rock")
    {
		notify_fail("You fail to tie the rope there. Perhaps on a rock.\n");
		return 0;
    }

    if (tied)
    {
		notify_fail("There's already a rope tied here, no need for another.\n");
		return 0;
    }

    object roomExists = query_master_instance_pointer()->query_rooms(x, y, z+1);

    if (roomExists == 0)
    {
        notify_fail("There's no need to attach a rope here.\n");
        return 0;
    }
    else
    {
        tp->catch_msg("You tie the rope to a large rock.\n");
        tell_room(environment(tp), QCTNAME(tp) + " ties the rope to a large rock.\n", tp);

        tied = rope;
        return 1;
    }

}

untie_object(rope)
{
    object tp = this_player();

    if (tied == rope)
	{
        if (query_thrown_rope())
        {
            tp->catch_msg("You untie the rope and it falls into the hole. Perhaps you should have <pull>ed it before.\n");
            tell_room(environment(tp), QCTNAME(tp) + " unties the rope and it falls into the hole.\n", tp);

            object roomExists = query_master_instance_pointer()->query_rooms(x, y, z+1);

            roomExists->remove_exit("up");

            roomExists->remove_item("roof" );
            roomExists->add_item(({ "roof" }),
                "There's a hole in the roof.\n");

            tell_room(roomExists, "A rope falls from above you, you could say you're stranded now.\n", this_player());

            thrown_rope = 0;

            tied->move(roomExists);
        }
        else
        {
            tp->catch_msg("You untie the rope from a large rock.\n");
            tell_room(environment(tp), QCTNAME(tp) + " unties the rope from a large rock.\n", tp);
        }

		tied = 0;
		return 1;
    }

    return 0;
}