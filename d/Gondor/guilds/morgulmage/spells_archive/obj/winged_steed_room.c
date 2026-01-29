inherit "/std/room";

mapping steeds = ([ ]);

void create_room() {
    set_short("winged steed room");
    set_long("Room to house the winged steeds as they are in flight.\n");
}

object find_steed_for_mage(object mage) {
    return steeds[mage->query_real_name()];
}

void register_steed_for_mage(object mage, object steed) {
    object current_steed = find_steed_for_mage(mage);
    if (objectp(current_steed) && current_steed != steed) {
        current_steed->take_off_and_remove();
    }

    steeds[mage->query_real_name()] = steed;
}


public void enter_inv( object ob, object from )
{
    ::enter_inv( ob, from );

    if (!objectp( ob ) || !objectp( from ) || living( ob ))
    {
        return;
    }
    
    set_alarm(0.1, 0.0, &tell_room( from, "The "+ ob->short()+ " falls down "
        + "through the clouds to the ground far below and is lost.\n" ));
    set_alarm(0.5, 0.0, ob->remove_object);
}
