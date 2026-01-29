
/******** Module: Cleaning tools for the ReusablePartsModule **************
 *                           flag:   8                                    *
 **************************************************************************/

/* Of course you may clean other things than the ReusablePartsModule
 [32m * but you might well lose the Cleaning Tools in the progress. [0m
 * This module doesn't break if used properly.
 */
void
other_clean(string how, string what)
{
    object ob;
    int i;
    string obj_name;

    what = lower_case(what);
    if(!(ob = P(what, TP)))
    {        
        write(C(how) + " what?\n");
        return;
    }
    obj_name = ob->short();
    for(i=0;i<3;i++)     /* Chance of breaking 3 times as high */

    {
        if(flag(8,1) == -1)
        {
            write("You start to " + how + " the " + obj_name 
              + " but ");
            if(how == "goil")
                write("the feather breaks.\n");
            else
                write("the cleaning rag tears.\n");

            write("The cleaning tools have been designed for more "
              + "delicate purposes.\nAngrily, you dump the now "
              + "incomplete and thus useless module.\n");
            return;
        }
    }
    write("Carefully, you " + how + " the " + obj_name + ".\n");
 [33m    say(QCTNAME(TP) + " carefully " + how);  [0m
    if(how == "polish") 
 [33m        say("e"); [0m
 [33m    say("s " + POSSESSIVE(TP) + " " + obj_name + ".\n"); [0m
}

int
clean(string str)
{
    object rpm;
    string name;

    str = C(str);
    NF("You forgot to attach this module.\n");
    if(!(flag(8,0)))
        return 0;
    if(!(rpm = P("_reusable_parts_module_", TP)))
    {
        other_clean("clean", str);  /* Wants to clean something else */
        return 1;
    }
 [32m    if(str != (C(name = rpm->get_name())) && str != "Reusablepartsmodule" [0m
      && str != "ReusablePartsModule")
    {             
        other_clean("clean", str);  /* Wants to clean something else */
        return 1;
    }
    NF("Clean what?\n");
    if(name == "_rpm_")  /* ReusablePartsModule on set_no_show() */
        return 0;



    write("You carefully clean your ");
 [33m    say(QCTNAME(TP) + " carefully cleans " + POSSESSIVE(TP) + " "); [0m
    if(name == "reusablepartsmodule")
    {     
        write("ReusablePartsModule");
 [33m        say("collection of parts"); [0m
    }
    else
        tell_room(E(TP), C(name));
    tell_room(E(TP), " inspecting each piece in turn.\n");
    rpm->reduce_wear_out();   
    return 1;
}

int
goil(string str)
{
    object rpm;
    string name;

    str = C(str);
    NF("You forgot to attach this module.\n");
    if(!(flag(8,0)))
        return 0;
    if(!(rpm = P("_reusable_parts_module_", TP)))
    {
        other_clean("goil", str);  /* Wants to oil something else */
        return 1;
    }
 [32m    if(str != (C(name = rpm->get_name())) && str != "Reusablepartsmodule" [0m
      && str != "ReusablePartsModule")
    {             
        other_clean("goil", str);  /* Wants to oil something else */
        return 1;
    }
    NF("Oil what?\n");
    if(name == "_rpm_")  /* ReusablePartsModule on set_no_show() */
        return 0;

    write("You squirt some oil onto the feather, then dab it into your ");
 [33m    say(QCTNAME(TP) + " squits some oil onto a feather, then dabs it into a "); [0m
    if(name == "reusablepartsmodule")
    {     
        write("ReusablePartsModule.\n");
 [33m        say("collection of parts.\n"); [0m
    }
    else
        tell_room(E(TP), C(name) + ".\n");
    rpm->reduce_wear_out();
    return 1;
}

int
polish(string str)
{
    object rpm;
    string name;

    str = C(str);
    NF("You forgot to attach this module.\n");
    if(!(flag(8,0)))
        return 0;
    if(!(rpm = P("_reusable_parts_module_", TP)))
    {
        other_clean("polish", str);  /* Wants to polish something else */
        return 1;
    }
 [32m    if(str != (C(name = rpm->get_name())) && str != "Reusablepartsmodule" [0m
      && str != "ReusablePartsModule")
    {             
        other_clean("polish", str);  /* Wants to polish something else */
        return 1;
    }
    NF("Polish what?\n");
    if(name == "_rpm_")  /* ReusablePartsModule on set_no_show() */
        return 0;


    write("You meticulously polish your ");
 [33m    say(QCTNAME(TP) + " meticulously polishes " + POSSESSIVE(TP) + " "); [0m
    if(name == "reusablepartsmodule")
    {     
        write("ReusablePartsModule");
 [33m        say("collection of parts"); [0m
    }
    else
        tell_room(E(TP), C(name));
    tell_room(E(TP), " with a soft cleaning rag.\n");
    rpm->reduce_wear_out();
    return 1;
}


