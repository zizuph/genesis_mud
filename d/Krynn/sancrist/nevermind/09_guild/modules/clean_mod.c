/******************* module: CleanlinessModule ****************************
 *                   flag:   11                                           *
 **************************************************************************/

void
wash_msg()
{
    int a;

    a = random(4);
    if(a == 0)

    {
[32m        write("Your gizmo gives a prolonged rumble.\n");[0m
[32m        say(QCTNAME(TP) + "'s gizmo gives a prolonged rumble.\n");[0m
        return;
    }
    if(a == 1)
    {
        write("A cloud of steam escapes from your gizmo.\n");
[33m        say("A cloud of steam escapes from " + POSSESSIVE(TP) + " gizmo.\n");[0m
        return;
    }
    if(a == 2)
    {
        write("Soap drips from the bottom of your gizmo.\n");
[33m        say("Soap drips from the bottom of " + POSSESSIVE(TP) + " gizmo.\n");[0m
        return;
    }
    if(a == 3)
    {
        write("There's a bubbling noise from your gizmo.\n");
[33m        say("There's a bubbling noise from " + POSSESSIVE(TP) + " gizmo.\n");[0m
        return;
    }
}

int
wash(string str)
{
    NF("You forgot to attach that module.\n");
    if(!flag(11,0))
        return 0;

    NF("You may only wash yourself.\n");
    if(P(str, E(TP)))
        return 0;
    NF("Wash whom?\n");
    if(str != "myself" && str != "me" && lower_case(str) != (TP->query_real_nam-
e()))
        return 0;
    NF("It's too dark to wash yourself.\n");
    if(!CAN_SEE_IN_ROOM(TP))
    {
        UNSET_WASH(TP);
        UNSET_WASH_SUCCESS(TP);
        return 0;
    }
    NF("Your PersonalCleanlinessAndRefreshmentModule is still busy.\n");
    if(QUERY_WASH(TP) > 3)
        return 0;

    NF("Yes, you're already washing yourself.\n");
    if(QUERY_WASH(TP))
        return 0;

    SET_WASH(TP, 1);
    write("You prepare yourself for extensive washing.\n");
[33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n");[0m
    return 1;
}

int
wash_me(string str)
{
    int a;
    string result;

    if(str != "lever" && str != "the lever")
        return 0;

    if(QUERY_WASH(TP) > 3)
    {
        write("Your PersonalCleanlinessAndRefreshmentModule is still busy.\n");
        return 1;
    }

    result = steamengine_check(TP);
    if(result == "What?\n")
        result = "You'll need a steamengine first.\n";
    if(result != "ok")
    {
        UNSET_WASH(TP);
        write(result);
        return 1;
    }

    if(!CAN_SEE_IN_ROOM(TP))
    {
        write("It's too dark to do that.\n");
        UNSET_WASH(TP);
        UNSET_WASH_SUCCESS(TP);
        return 1;
    }

    a = random(4);
    if(a > 1)
        if(flag(11,1) == -1)
        {
            UNSET_WASH(TP);
            UNSET_WASH_SUCCESS(TP);
            return 1;
        }

[32m    write("You pull the lever of your PersonalCleanlinessAndRefreshmentModule.\-[0m
n");
[33m    say(QCTNAME(TP) + " pulls a lever on " + POSSESSIVE(TP) + " gizmo.\n");[0m
    wash_msg();

    if(QUERY_WASH(TP) == 1)
    {
        if(a == 0)
        {
            write("A mixture of steaming hot soap and water pours from the
DispensingFunnel "
              + "into your cupped hands. You scrub yourself vigorously.\n");
[33m            say("A mixture of steaming hot soap and water pours into " +[0m
POSSESSIVE(TP)
[35m              + " cupped hands. " + C(PRONOUN(TP)) + " scrubs " + OBJECTIVE(TP)[0m
+ "self "
              + "vigorously.\n");
            find_gizmo(TP)->reduce_water();            
            SET_WASH_SUCCESS(TP, 4);
        }
        if(a == 1)
        {
            write("A mixture of steaming hot soap and water pours from the
DispensingFunnel "
              + "into your face. You blow bubbles as you leisurously wash
yourself.\n");

[33m            say("A mixture of steaming hot soap and water pours into " +[0m
POSSESSIVE(TP)
              + " face. " + C(PRONOUN(TP)) + " blows bubbles as " + PRONOUN(TP)
+ " leisurely "
              + "washes " + OBJECTIVE(TP) + "self.\n");
            find_gizmo(TP)->reduce_water();            
            SET_WASH_SUCCESS(TP, 4);
        }
        if(a == 2)
        {
            write("Hot water streams from the DispensingFunnel. A few moments
later, there's a "
[32m              + "spurt of soap. You quickly mix the two together.\n");[0m
[33m            say("Hot water streams from a DispensingFunnel on " +[0m
POSSESSIVE(TP) + " gizmo. "
              + "A few moments later, there's a spurt of soap. " +
C(PRONOUN(TP)) + " quickly "
[32m              + "mixes the two together.\n");    [0m
            find_gizmo(TP)->reduce_water();            
            SET_WASH_SUCCESS(TP, 2);
        }
        if(a == 3)
        {
            write("Viscous hot soap oozes from the DispensingFunnel,
unfortunately without "
              + "accompanying water. You're covered with thick soapy goo.\n");
[33m            say("Viscous hot soap oozes from a DispensingFunnel, unfortunately[0m
without "
              + "accompanying water. " + C(PRONOUN(TP)) + " is covered with
thick soapy goo.\n");
            SET_WASH_SUCCESS(TP, 1);
        }
        SET_WASH(TP, 2);
        return 1;
    }

    if(QUERY_WASH(TP) == 2)
    {
        if(a == 0)
        {
            write("Clean hot water gushes from the DispensingFunnel. You slowly
rinse "
              + "youself, luxurating in the warmth.\n");
[33m            say("Clean hot water gushes from a DispensingFunnel on " +[0m
POSSESSIVE(TP)
              + " gizmo. " + C(PRONOUN(TP)) + " slowly rinses " + OBJECTIVE(TP)
+ "self, "
              + "luxurating in the warmth.\n");
            find_gizmo(TP)->reduce_water();            
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 4);
        }
        if(a == 1)
        {
[35m            write("The gizmo gurgles as hot water pours from the DispensingFunn-[0m
el. You "
              + "splash it literally all about your person to remove all traces
of "
              + "soap.\n");
[33m            say(C(POSSESSIVE(TP)) + " gizmo gurgles as hot water pours from the[0m
DispensingFunnel. "
              + C(PRONOUN(TP)) + " splashes it literally all about " +
POSSESSIVE(TP)
              + " person to remove all traces of soap.\n");

            find_gizmo(TP)->reduce_water();
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 3);
        }
        if(a == 2)
        {
            write("Hot water flows from the DispensingFunnel. Unfortunately it
is slightly "
              + "soapy, so your rinse is only partially effective.\n");
[33m            say("Hot water flows from a DispensingFunnel on " + POSSESSIVE(TP)[0m
+ " gizmo. "
              + C(PRONOUN(TP)) + " rinses " + OBJECTIVE(TP) + "self.\n");
            find_gizmo(TP)->reduce_water();
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 2);        }
        if(a ==  3)
        {
[35m            write("Slightly warm water tickles from the funnel. You manage to[0m
rinse off some "
              + "soap.\n");
[33m            say("Water tickles from a funnel on " + POSSESSIVE(TP) + " gizmo. "[0m
              + C(PRONOUN(TP)) + " manages to rinse off some soap.\n");
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 1);
        }
        SET_WASH(TP, 3);
        return 1;
    }        

    if(QUERY_WASH(TP) == 3)

    {
        if(a == 0)
        {
            write("A mechanical arm extends from the TowelExtrusionUnit and
hands you a soft, "
              + "warm towel. You dry yourself thouroughly and return the
towel.\n");
[33m            say("A mechanical arm extends from " + POSSESSIVE(TP) + " gizmo and[0m
hands "
              + OBJECTIVE(TP) + " a soft, warm towel. " + C(PRONOUN(TP)) + "
dries "
              + OBJECTIVE(TP) + "self thouroughly.\n");
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 3);
        }
        if(a == 1)
        {
            write("A mechanical arm creaks out from the TowelExtrusionUnit and
drops a soft "
              + "towel. You catch it just before it hits the ground, dry
yourself and " 
              + "drape the towel over the mechanical arm which slowly and
noisily retracts.\n");
[33m            say("A mechanical arm creaks out from " + POSSESSIVE(TP) + " gizmo[0m
and drop a "
              + "soft towel. " + C(PRONOUN(TP)) + " catches it just before it
hits the ground, "
              + "dries " + OBJECTIVE(TP) + "self and drapes the towel over the
arm which "
              + "slowly and noisily retracts.\n");
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 3);
        }
        if(a == 2)
        {
            write("There's a grinding noise from the TowelExtrusionUnit and a
raveled strip of "

              + "toweling drops into your hands. It disintegrates before you
quite finished "
              + "drying.\n");
[33m            say("There's a grinding noise from " + POSSESSIVE(TP) + " gizmo and[0m
a strip of "
              + "toweling drops into " + POSSESSIVE(TP) + " hands. It
disintegrates before "
              + PRONOUN(TP) + " quite finished drying.\n");
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 2);                  
        }
        if(a == 3)
        {
            write("There's a load clank from your gimzo but nothing else
happens. You shake "
              + "the water off as best as you can.\n");
[33m            say("There's a loud clank from " + POSSESSIVE(TP) + " gizmo but[0m
nothing else "
nothing else "
              + "happens. " + C(PRONOUN(TP)) + " shakes " + OBJECTIVE(TP) +
"self like a "
[32m              + "wet dog to get rid of the water.\n");[0m
            SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 1);
        }
        SET_WASH(TP, 4);
        set_alarm(5.0, -1.0, "end_wash", TP);
    }
    return 1;
}

void
end_wash(object player)
{
    int success, flag;
    object obj;

    success = QUERY_WASH_SUCCESS(TP);
    UNSET_WASH(player);
    UNSET_WASH_SUCCESS(TP);

    // Dirty from Kalad

    if(player->query_prop("_live_i_dirty"))
    {
        player->add_prop("_live_i_dirty", player->query_prop("_live_i_dirty") 
          - success * 25);
        if(success > 8 || player->query_prop("live_i_dirty") < 1)
        {
            player->remove_prop("_live_i_dirty");
            if(obj = P("dirty", player))
                obj->remove_object();
        }
    }
    // Dirty from the mud puddle in /d/Shire/common/greenway/gw2

    if(success > 7)

        player->remove_shadow("/d/Shire/common/greenway/dirty_shadow");

    // Stinking from the skunk in Krynn

    if(obj = P("stink", player) && P("spray", player))
    {
        if(success > 8)
        {
            obj->remove_object();
            player->catch_msg("Ahh, how refreshing to be clean again. "
              + "You don't smell of skunk anymore.\n");
            tell_room(E(player), QCTNAME(player) + " doesn't stink any"
              + "more.\n", player);
        }
        else
[32m            player->catch_msg("You feel fresher now but still smell of "[0m
              + "skunk!\n");
        flag = 1;
    }     

    // General cleanliness

    if(flag)
        return;


    if(success > 8)
        player->catch_msg("Ahh, how refreshing to be clean again.\n");
    if(success == 8)
[32m        player->catch_msg("You feel much fresher now.\n");[0m
    if(success == 7)
        player->catch_msg("You aren't nearly as scruffy as before.\n");
    if(success == 6)
        player->catch_msg("You definitivly smell better now.\n");
    if(success < 6)
[32m        player->catch_msg("You feel a bit fresher now but a second go wouldn't[0m
be bad "
          + "either.\n");
}   



