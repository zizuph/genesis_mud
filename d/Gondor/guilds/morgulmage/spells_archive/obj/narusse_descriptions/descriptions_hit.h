int hit_statuesque(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("You stand statuesque, luring your opponent to "
        + "an easy attack. As " + QTNAME(enemy) + " approaches, you "
        + "unleash a flurry of strikes with the " + weapon->short()
        + ". Your assaults " + damage + " " + enemy->query_objective()
        + " on the " + location + ".\n");

    enemy->catch_msg(QCTNAME(wielder) + " stands suddenly still, "
        + "illuminated by the flickering flames of the " + weapon->short()
        + ". Enticed by " + wielder->query_posessive() + " inactivity, "
        + "you cautiously approach, seeking that lethal opening. With a "
        + "flurry of motion, " + QTNAME(wielder) + " springs to life and "
        + damage + " your " + location + ".\n");

    wielder->tell_watcher(QCTNAME(wielder) + " suddenly stiffens, motionless "
        + "as " + QTNAME(enemy) + " approaches. Closer... closer... closer; "
        + "A flurry of motion befalls your sight as " + QTNAME(wielder)
        + " springs to life leaving an acrid smell in the air. You notice "
        + "the " + location + " of " + QTNAME(enemy) + " is smouldering.\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_kneel(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("You kneel humbly to the greatness of Sauron, defiant "
        + "in the presense of your enemies. As " + QTNAME(enemy) + " perceives "
        + "an opening, you grasp the hilt of your " + weapon->short() + " and "
        + "with a mighty swing, " + damage + " " + enemy->query_possessive() 
        + " " + location + ".\n");
    
    enemy->catch_msg("You perceive an opening in your opponent's defences. " 
        + QCTNAME(wielder) + " is actually kneeling! You hastily approach, "
        + "heart pounding at the moronic over-confidence of Mordor, but your "
        + "approach is suddenly halted as a sickeningly numb feeling "
        + "surrounds your " + location + ", lain open by the " 
        + weapon->short() + ".\n");
    
    wielder->tell_watcher("You can see " + QTNAME(wielder) + " kneel with "
        + "the " + weapon->short() + " upright before " 
        + wielder->query_objective() + ". " + QCTNAME(enemy) + " suddenly "
        + "approaches as if perceiving an opening but is harshly thwarted "
        + "by an upward thrust by " + QTNAME(wielder) + ".\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_brandish(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("You brandish the " + weapon->short() + " in front of "
        + QTNAME(enemy) + ", disorienting " + enemy->query_objective()
        + ". Sensing an opening, you lunge forward and feel the fell weapon "
        + damage + " " + enemy->query_possessive() + " " + location + ".\n");
    
    enemy->catch_msg(QCTNAME(wielder) + " brandishes the " + weapon->short() 
        + "like a weaponsmaster. Such skill sends a chill of doubt through "
        + "your very soul. Before you can react, you feel the bite of the "
        + "weapon as it " + damage + " your " + location + ".\n");
    
    wielder->tell_watcher("With the skill of someone trained in the fine "
        + "arts of combat, " + QTNAME(wielder) + " brandishes the "
        + weapon->short() + " before " + QTNAME(enemy) + " leaving "
        + enemy->query_objective() + " momentarily dazed. Seconds later, "
        + "you see the weapon connect with its intended target.\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_robe(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("With a flourish of your black robe, you are able "
        + "to entagle " + QTPNAME(enemy) + " weapon, leaving you to do as "
        + "you wish. You take the opportunity to " + damage + " " 
        + enemy->query_possessive() + " " + location + " with your " 
        + weapon->short() + ".\n");
    
    enemy->catch_msg(QCTNAME(wielder) + " encases your weapon within the "
        + "folds of " + wielder->query_possessive() + " robes. Unable to "
        + "parry the assault, the " + weapon->short() + " " + damage 
        + " your " + location + ".\n");
    
    wielder->tell_watcher(QCTPNAME(enemy) + " weapon disappears in a sudden "
        + "flourish of the black robe of " + QTNAME(wielder) + ". Left "
        + "defenseless, " + QTNAME(enemy) + " feels the sting of a fell "
        + "attack.\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_flail(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("You swing the " + weapon->short() + " causing "
        + QTNAME(enemy) + " to flail about mindlessly. As a result, your "
        + "blow " + damage + " " + enemy->query_possessive() + " "
        + location + ".\n");
    
    enemy->catch_msg(QCTPNAME(wielder) + " stance shifts causing a tremor "
        + "of panic to course through your limbs. As you flail about in "
        + "attempt to avoid any incoming blows, the " + weapon->short()
        + " " + damage + " your " + location + ".\n");
    
    wielder->tell_watcher("As " + QTNAME(wielder) + " swings the "
        + weapon->short() + " through the air " + QTNAME(enemy) + " begins "
        + "to flail about. The ruse was met with moderate success as they "
        + "seem to have avoided the brunt of the assault.\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_thrust(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("As you thrust the " + weapon->short() + " toward "
        + QTNAME(enemy) + ", you notice that " + enemy->query_pronoun() 
        + " moves almost completely out of the way allowing you to "
        + damage + " the " + location + ", causing a sickening smell to "
        + "emanate.\n");
    
    enemy->catch_msg("You notice " + QTNAME(wielder) + " thrusting at you "
        + "with the " + weapon->short() + ". With astounding agility, you "
        + "barely escape the assault. A foul odor reaches your nostrils as "
        + "you realize the attack " + damage + " your " + location
        + " leaving behind a sizzling gash.\n");
    
    wielder->tell_watcher("With a feint, " + QTNAME(enemy) + " leaps aside "
        + "the thrust of " + QTNAME(wielder) + " with the " + weapon->short()
        + ", however a tainted odor assaults your nose as you realize the "
        + "dodge was not completely successful.\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_flurry(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("Through a flurry of assaults with your " 
        + weapon->short() + ", you " + damage + " " + QTNAME(enemy)
        + " ferociously, causing flames to ignite " + enemy->query_possessive()
        + " " + location + ".\n");
    
    enemy->catch_msg(QCTPNAME(wielder) + " arm seems to blur leaving you "
        + "powerless to avoid " + wielder->query_possessive() + " assault. "
        + "A searing pain resonates from your " + location + " as the "
        + weapon->short() + " " + damage + " it viciously.");
    
    wielder->tell_watcher(QCTPNAME(enemy) + " " + location + " is suddenly "
        + "engulfed in flames after a barrage of assaults from the " 
        + weapon->short() + " wielded by " + QTNAME(wielder) + ".\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_sweep(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("A feral grin on your face, you masterfully sweep "
        + "the " + weapon->short() + " through the air toward " 
        + QTNAME(enemy) + " " + damage + " from hip to shoulder, leaving "
        + enemy->query_objective() + " writhing in pain.\n");

    wielder->tell_watcher("A grizzly scene unfolds before you as "
        + QTNAME(wielder) + " savagly " + damage + " " + location 
        + " from hip to opposing shoulder with " + wielder->query_possessive()
        + " " + weapon->short() + ".\n",
        enemy, ({ enemy, wielder }));
    
    enemy->catch_msg("An evil glint passes across " + QTPNAME(wielder) 
        + "eyes as " + wielder->query_pronoun() + " swings at you with "
        + "the " + weapon->short() + ". As though a molten brand lay on your "
        + "skin, the weapon " + damage + " you from tip to stern causing an "
        + "uncontrollable scream to escape from your gritted teeth.\n");
    enemy->command("$scream");
        
    return 1;
}

int hit_darkness(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("You reach out with your hand toward " + QTNAME(enemy)
        + " whispering the word \"dae\".  With the invocation and a small "
        + "trickle of power, you see " + QTPNAME(enemy) + " eyes unfocus "
        + "leaving them vulnerable. The " + weapon->short() + ", seemingly "
        + "of its own accord, " + damage + " " + enemy->query_possessive()
        + " " + location + " leaving behind a rotten odor.\n");
    
    enemy->catch_msg(QCTNAME(wielder) + " reaches toward you with a gnarled "
        + "hand and " + wielder->query_pronoun() + " whispers something "
        + "inaudible.... Darkness!  You can't see! The sound of a "
        + "high-pitched whine and flickering flames assaults your ears. "
        + "The shock of a searing pain on your " + damage + " causes the "
        + "shadows in your eyes to violently dissapate, leaving a blurry "
        + "visage before you.\n");
    
    wielder->tell_watcher("From beneath a shadowed hood, you hear a short "
        + "hiss as " + QTNAME(wielder) + " reaches toward " + QTNAME(enemy)
        + "with a gnarled fist, causing " + enemy->query_objective()
        + " to stagger. The " + weapon->short() + " leaps toward " 
        + QTNAME(enemy) + " " + damage + " " + enemy->query_possessive()
        + " " + location + ".\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

int hit_opening(object wielder, object enemy, object weapon,
    string location, string damage)
{
    wielder->catch_msg("With feral speed you arrogantly parry a pathetic "
        + "excuse for an attack from " + QTNAME(enemy) + " with a flick of "
        + "your wrist. Instantly, an opening appears and you sieze it, "
        + damage + " " + enemy->query_objective() + " on the " + location
        + ".\n");
    
    enemy->catch_msg("You swing mightily at " + QTNAME(wielder) + " but "
        + wielder->query_pronoun() + " parries the attack with a lazy flick. "
        + "A feeling of great vulnerability assaults you. Suddenly the "
        + weapon->short() + " " + damage + " your " + location + ".\n");
    
    wielder->tell_watcher(QCTNAME(enemy) + " seems to stagger as "
        + QTNAME(wielder) + " deftly parries a blow and counters! The "
        + weapon->short() + " " + damage + " " + QTNAME(enemy) + " on the "
        + location + ".\n",
        enemy, ({ enemy, wielder }));
        
    return 1;
}

#define HIT_MESSAGES \
    ({ \
        ({ hit_statuesque, 0, 100, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
        ({ hit_kneel, 0, 100, ({ W_SLASH }) }), \
        ({ hit_brandish, 0, 100, ({ W_IMPALE, W_SLASH }) }), \
        ({ hit_robe, 0, 100, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
        ({ hit_flail, 0, 5, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
        ({ hit_thrust, 0, 5, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
        ({ hit_thrust, 30, 100, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
        ({ hit_sweep, 30, 100, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
        ({ hit_darkness, 10, 100, ({ W_SLASH }) }), \
        ({ hit_opening, 0, 100, ({ W_IMPALE, W_SLASH, W_BLUDGEON }) }), \
    })
