
void
refill_lava()
{
    lava = LAVA_MAX;
}

int
do_refill_lava(string str)
{

    object tp = this_player();

    string *data;
    string item = "";
    string place;

    if (str)
    {
        data = explode(str, " with ");
        if (sizeof(data) > 1)
        {
            item = data[0];
            place = data[1];
        }
        else
        {
            item = data[0];
            place = "";
        }
    }

    if (item == "tank" || item == "lava tank")
    {
        if (is_lava_nearby()) {
            refill_lava();

            tp->catch_msg("You press the refill button in the lava tank and a few extensible " +
                "tubes find the near lava and start extracting from it.\n" +
                "After a few seconds it's finished and the tubes go back into place.\n");
            tell_room(environment(tp), QCTNAME(tp) + " presses a button in "+tp->query_possessive()+
                " pickaxe and a few extensible tubes find the near lava and start extracting from it.\n" +
                "After a few seconds it's finished and the tubes go back into place.\n", tp);
        }
        else
        {
            tp->catch_msg("You press the refill button in the lava tank and a few extensible " +
                "tubes pop out, but are not able to find any lava deposits.\n" +
                "After a few seconds the tubes go back into place.\n");
            tell_room(environment(tp), QCTNAME(tp) + " presses a button in "+tp->query_possessive()+
                " pickaxe and a few extensible tubes pop out, but dont do anything.\n" +
                "After a few seconds the tubes go back into place.\n", tp);            
        }
        return 1;
    }

    notify_fail("You mean refill tank?\n");
    return 0;       
}
