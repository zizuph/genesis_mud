#define EMYN_ARNEN_SCABBARD "_emyn_arnen_scabbard"
private int filter_narusse_enhanced(object ob) 
{
    object *effects = ob->query_magic_effects();
    if(!pointerp(effects)) return 0;
    foreach(object effect : effects) {
        if(effect->query_shadow_filename() == MORGUL_SPELL_OBJ_DIR + "narusse_sh") return 1;
    }    
    return 0;
}

private object *narusse_inventory(object player) 
{
    object *result = all_inventory(player);
    object scabbard = present(EMYN_ARNEN_SCABBARD, player);
    if (objectp(scabbard)) result += all_inventory(scabbard);
    return result;
}

private object find_narusse_weapon(object player, string args, int allow_no_arguments)
{
    if((args == 0) || (args == "")) 
    {
        if(allow_no_arguments) 
        {
            object *narusse_weapons = filter(narusse_inventory(player), filter_narusse_enhanced);
            if (!sizeof(narusse_weapons)) {
                notify_fail("You are not carrying any narusse enhanced weapons.\n");
                return 0;
            }
            return narusse_weapons[0];
        } else {
            return 0;
        }
    }
    
    object *matches = PARSE_COMMAND(args, all_inventory(player), "[the] %i");
    if(sizeof(matches) == 0) 
    {
        return 0;
    }
    
    if(sizeof(matches) > 1) {
        notify_fail("Please select a specific weapon.\n");
        return 0;
    }
    
    if(!filter_narusse_enhanced(matches[0])) {
        notify_fail("The " + matches[0]->short() + " is not a "
            + "narusse enhanced weapon.\n");
        return 0;
    }
    
    return matches[0];
}

private object get_effect(object weapon)
{
    object *effects = weapon->query_magic_effects();
    if(!pointerp(effects)) return 0;
    foreach(object effect : effects) {
        if(effect->query_shadow_filename() == MORGUL_SPELL_OBJ_DIR + "narusse_sh"
            && effect->query_effect_target() == weapon) return effect;
    }
    return 0;
}

public int narusse_ignite(string args)
{
    notify_fail("Ignite what?\n");
    
    object weapon = find_narusse_weapon(this_player(), args, query_verb() == "nignite");
    if (!objectp(weapon)) return 0;

    if(weapon->is_narusse_enhanced()) 
    {
        notify_fail("The " + weapon->short() + " is already set aflame.\n");
        return 0;
    }
    
    if(weapon->query_wielded() != this_player()) 
    {
        notify_fail("You are not wielding the " + weapon->short() + ".\n");
        return 0;
    }
    
    object effect = get_effect(weapon);
    effect->query_shadow_object()->get_description()->display_ignite_message(this_player(), weapon);
    effect->query_shadow_object()->execute_enhancement(this_player(), weapon);
    effect->query_shadow_object()->display_flicker_message();
    return 1;
}

public int narusse_extinguish(string args)
{
    notify_fail("Extinguish what?\n");
    
    object weapon = find_narusse_weapon(this_player(), args, query_verb() == "nextinguish");
    if (!objectp(weapon)) return 0;
    
    if(!weapon->is_narusse_enhanced()) 
    {
        notify_fail("The " + weapon->short() + " is not set aflame.\n");
        return 0;
    }

    object effect = get_effect(weapon);
    effect->query_shadow_object()->get_description()->display_extinguish_message(this_player(), weapon);
    effect->query_shadow_object()->remove_enhancement();
    return 1;
}

private mixed can_wield(object player, object weapon) 
{
    int left_occupied = objectp(player->query_tool(W_LEFT));
    int right_occupied = objectp(player->query_tool(W_RIGHT));
    
    if ((weapon->query_hands() == W_LEFT) && left_occupied)
        return "Your left hand is occupied!\n";
        
    if ((weapon->query_hands() == W_RIGHT) && right_occupied)
        return "Your right hand is occupied!\n";
    
    if ((weapon->query_hands() == W_ANYH) && left_occupied && right_occupied)
        return "You have no hand free to wield the weapon!\n";
        
    if ((weapon->query_hands() == W_BOTH) && (left_occupied || right_occupied))
        return "You need both hands free to wield the weapon!\n";
        
    return 0;
}

private string describe_move_error(int error) 
{
    switch(error) {
        case 1: return "The sword is to heavy.\n";
        default: return "Unable to remove the sword from the scabbard (" + error + ").\n";
    }
}

public int narusse_threaten(string args)
{
    mixed result;
    
    notify_fail("Threaten who?\n");
    if (!args || !strlen(args)) return 0;
    
    object *oblist = parse_this(args, "[the] %l");
    if (!sizeof(oblist)) return 0;
    
    if (sizeof(oblist) != 1) {
        notify_fail("You can only threaten one target at a time.\n");
        return 0;
    }
    
    object target = oblist[0];
    
    object weapon = find_narusse_weapon(this_player(), "", 1);
    if (!objectp(weapon)) return 0;
    
    object effect = get_effect(weapon);
    
    if (weapon->query_wielded() == this_player()) {
        if (weapon->is_narusse_enhanced()) {
            write("You threatingly swing your " + weapon->short()
                + " in the direction of " + target->query_the_name(this_player())
                + ", the flaming tip slashing centimeters from "
                + target->query_possessive() + " face.\n");
            
            say(QCTNAME(this_player()) + " threatingly swings "
                + this_player()->query_possessive() + " " 
                + weapon->short() + " in the direction of "
                + QTNAME(target) + ", the flaming tip slashing "
                + "centimeters from " + target->query_possessive()
                + " face.\n", ({ this_player(), target }));
                
            target->catch_tell(this_player()->query_The_name(target)
                + " threatingly swings " + this_player()->query_possessive()
                + " " + weapon->short() + " in your direction, the "
                + "flaming tip slashing centimeters from your face.\n");
                
            return 1;
        } else {            
            write("You viciously swing your " + weapon->short()
                + " in the direction of " + target->query_the_name(this_player())
                + ", the tip slashing centimeters from "
                + target->query_possessive() + " face. As you rasp "
                + "'narusse', the weapon bursts into flames.\n");
                
            say(QCTNAME(this_player()) + " viciously swings "
                + this_player()->query_possessive() + " " 
                + weapon->short() + " in the direction of "
                + QTNAME(target) + ", the tip slashing centimeters "
                + "from " + target->query_possessive() + " face. As "
                + this_player()->query_pronoun() + " rasps "
                + "something unintelligible, the weapon bursts into flames.\n",
                ({ this_player(), target }));
                
            target->catch_tell(this_player()->query_The_name(target)
                + " viciously swings " + this_player()->query_possessive()
                + " " + weapon->short() + " in your direction, the "
                + "tip slashing centimeters from your face. "
                + "As " + this_player()->query_pronoun() + " rasps something "
                + "unintelligible, the weapon bursts into flames.\n");
                
            effect->execute_enhancement(this_player(), weapon);
            return 1;
        }
    } else if (environment(weapon)->id(EMYN_ARNEN_SCABBARD)) {
        if (result = weapon->move(this_player())) {
            notify_fail(describe_move_error(result));
            return 0;
        }
        
        write("With a vicious swing, you draw your " + weapon->short()
            + " from the golden scabbard and point it in the "
            + "direction of " + target->query_the_name(this_player())
            + ". As you rasp 'narusse', the weapon bursts into flames.\n");
            
        say("With a vicious swing, " + QTNAME(this_player()) + " draws "
            + this_player()->query_possessive() + " " + weapon->short()
            + " and points it in the direction of " + QTNAME(target)
            + ". As " + this_player()->query_pronoun() + " rasps something "
            + "unintelligible, the weapon bursts into flames.\n",
            ({ this_player(), target }));
            
        target->catch_tell("With a vicious swing, " 
            + this_player()->query_the_name(target) + " draws " 
            + this_player()->query_possessive() + " " + weapon->short()
            + " and points it in your direction. As " 
            + this_player()->query_pronoun() + " rasps something "
            + "unintelligible, the weapon bursts into flames.\n");
            
        this_player()->add_prop(MORGUL_I_SUPPRESS_AUTOIGNITE, 1);
        if (stringp(result = weapon->command_wield())) {
            write(result);
        } else {
            effect->execute_enhancement(this_player(), weapon);
        }
        this_player()->remove_prop(MORGUL_I_SUPPRESS_AUTOIGNITE);
        
        return 1;
    } else {
        write("You viciously wield your " + weapon->short() + " and "
            + "swing it in the direction of " 
            + target->query_the_name(this_player()) + ". As you rasp "
            + "'narusse', the weapon bursts into flames.\n");
            
        say(QCTNAME(this_player()) + " viciously wields " 
            + this_player()->query_possessive() + " " + weapon->short() 
            + " and swings it in the direction of " + QTNAME(target)
            + ". As " + this_player()->query_pronoun() + " rasps "
            + "something unintelligible, the weapon bursts into flames.\n",
            ({ this_player(), target }));
            
        target->catch_tell(this_player()->query_The_name(target)
            + " viciously wields " + this_player()->query_possessive()
            + " " + weapon->short() + " and swings it in your direction. "
            + "As " + this_player()->query_pronoun() + " rasps something "
            + "unintelligible, the weapon bursts into flames.\n");

        this_player()->add_prop(MORGUL_I_SUPPRESS_AUTOIGNITE, 1);
        if (stringp(result = weapon->command_wield())) {
            write(result);
        } else {
            effect->execute_enhancement(this_player(), weapon);
        }
        this_player()->remove_prop(MORGUL_I_SUPPRESS_AUTOIGNITE);
        
        return 1;
    }
}