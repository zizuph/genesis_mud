/*
 * Cheiropoto Descriptions
 *
 * This file is included in the Cheiropoto Spell
 *
 * Created by Petros, October 2009
 */
 
public void
fire_concentrate_msg(object caster)
{
    string caster_message, watcher_message;
    
    switch (random(2))
    {
    case 0:
        caster_message = "Inflamed with the element of fire, you draw "
            + "upon its fierce strength.\n";
        watcher_message = QCTNAME(caster) + " concentrates deeply.\n";
        break;
        
    case 1:
    default:
        caster_message = "You close your eyes and focus on building "
            + "up the burning energy within you.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;        
    }
    
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

public void
water_concentrate_msg(object caster)
{
    string caster_message, watcher_message;
    
    switch (random(2))
    {
    case 0:
        caster_message = "Overflowing with the nature of the element "
            + "of water, you draw upon its fluid strength.\n";
        watcher_message = QCTNAME(caster) + " concentrates deeply.\n";
        break;
        
    case 1:
    default:
        caster_message = "You close your eyes and focus on building "
            + "up the mercurial energy within you.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;        
    }
    
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

public void
air_concentrate_msg(object caster)
{
    string caster_message, watcher_message;
    
    switch (random(2))
    {
    case 0:
        caster_message = "Suffused with the element of air, you draw "
            + "upon its gusty strength.\n";
        watcher_message = QCTNAME(caster) + " concentrates deeply.\n";
        break;
        
    case 1:
    default:
        caster_message = "You close your eyes and focus on building "
            + "up the volatile energy within you.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;        
    }
    
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

public void
earth_concentrate_msg(object caster)
{
        string caster_message, watcher_message;
    
    switch (random(2))
    {
    case 0:
        caster_message = "Solidly anchored with the element of earth, you draw "
            + "upon its indomitable strength.\n";
        watcher_message = QCTNAME(caster) + " concentrates deeply.\n";
        break;
        
    case 1:
    default:
        caster_message = "You close your eyes and focus on building "
            + "up the impregnable energy within you.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;        
    }
    
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

public void
fire_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
    int subelement = random(2);
    caster->add_prop(CHEIROPOTO_SUBELEMENT, subelement);
    switch (subelement)
    {
    case 0:
        caster_message = "Moving your hands in a rolling circular motion, "
            + "a spark between your palms grows into a brightly glowing "
            + "blue flaming sphere that you push towards " + QTNAME(target) 
            + ".\n";
        target_message = "Moving " + caster->query_possessive() + " hands "
            + "in a rolling circular motion, a spark between "
            + QTPNAME(caster) + " palms grows into a brightly "
            + "glowing blue flaming sphere that " + caster->query_pronoun()
            + " pushes towards you.\n";
        watcher_message = "Moving " + caster->query_possessive() + " hands "
            + "in a rolling circular motion, a spark between "
            + QTPNAME(caster) + " palms grows into a brightly "
            + "glowing blue flaming sphere that " + caster->query_pronoun()
            + " pushes towards " + QTNAME(target) + ".\n";
        break;
    
    case 1:
        caster_message = "Energetic sparks fly from your fingers and turn "
            + "into many brilliant streams of flame as they streak "
            + "towards " + QTNAME(target) + ".\n";
        target_message = "Energetic sparks fly from " + QTPNAME(caster)
            + " fingers and turn into many brilliant streams of flame as "
            + "they streak towards you.\n";
        watcher_message = "Energetic sparks fly from " + QTPNAME(caster)
            + " fingers and turn into many brilliant streams of flame as "
            + "they streak towards " + QTNAME(target) + ".\n";
        break;
    }
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
water_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
    int subelement = random(2);
    caster->add_prop(CHEIROPOTO_SUBELEMENT, subelement);
    switch (subelement)
    {
    case 0:
        caster_message = "The moisture in the air coalesces and freezes "
            + "into small hail stones that you direct towards "
            + QTNAME(target) + ".\n";
        target_message = "The moisture in the air coalesces and freezes "
            + "into small hail stones that " + QTNAME(caster) + " directs "
            + "towards you.\n";
        watcher_message = "The moisture in the air coalesces and freezes "
            + "into small hail stones that " + QTNAME(caster) + " directs "
            + "towards " + QTNAME(target) + ".\n";
        break;
    
    case 1:
        caster_message = "You move your hands back and forth horizontally "
            + "and form a swirling cluster of greenish fluid that you send "
            + "hurtling towards " + QTNAME(target) + ".\n";
        target_message = QCTNAME(caster) + " moves " + caster->query_possessive()
            + " hands back and forth horizontally and forms a swirling cluster "
            + "of greenish fluid that " + caster->query_pronoun() + " sends "
            + "hurtling towards you.\n";
        watcher_message = QCTNAME(caster) + " moves " + caster->query_possessive()
            + " hands back and forth horizontally and forms a swirling cluster "
            + "of greenish fluid that " + caster->query_pronoun() + " sends "
            + "hurtling towards " + QTNAME(target) + ".\n";
        break;
    }
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
air_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
    int subelement = random(2);
    caster->add_prop(CHEIROPOTO_SUBELEMENT, subelement);
    switch (subelement)
    {
    case 0:
        caster_message = "You twirl your arms in a circular motion, "
            + "summoning a howling gust of wind storms into the area, "
            + "quickly forming from a small vortex of air into a furious "
            + "tornado.\n";
        target_message = QCTNAME(caster) + " twirls " + caster->query_possessive()
            + " arms in a circular motion, summoning a howling gust of wind "
            + "into the area, quickly forming from a small vortex of air into "
            + "a furious tornado.\n";
        watcher_message = target_message;
        break;
    
    case 1:
        caster_message = "You hold your hands slightly apart and create "
            + "brilliant arcs of electricity between them. As they grow in "
            + "intensity, you thrust your arms towards " + QTNAME(target)
            + ".\n";
        target_message = QCTNAME(caster) + " holds " + caster->query_possessive()
            + " hands slightly apart and creates brilliant arcs of electricity "
            + "between them. As they grow in intensity, " + QTNAME(caster)
            + " thrusts " + caster->query_possessive() + " arms towards you.\n";
        watcher_message = QCTNAME(caster) + " holds " + caster->query_possessive()
            + " hands slightly apart and creates brilliant arcs of electricity "
            + "between them. As they grow in intensity, " + QTNAME(caster)
            + " thrusts " + caster->query_possessive() + " arms towards "
            + QTNAME(target) + ".\n";
        break;
    }
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
earth_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
    int subelement = random(2);
    caster->add_prop(CHEIROPOTO_SUBELEMENT, subelement);
    switch (subelement)
    {
    case 0:
        caster_message = "You stomp your feet, sending surges of "
            + "earthly elemental energy into the ground. The "
            + "ground heaves and trembles, sending rumbling "
            + "reverberations to all who are upon it.\n";
        target_message = QCTNAME(caster) + " stomps " + caster->query_possessive()
            + " feet, sending surges of earthly elemental energy into the "
            + "ground. The ground then heaves and trembles, sending "
            + "rumbling reverberations to all who are upon it.\n";
        watcher_message = target_message;
        break;
    
    case 1:
        caster_message = "You sweep your hands across your body in a flourish "
            + "and cause the sand to rise up from the ground. With a quick "
            + "flick, you send the shower of tiny particles towards "
            + QTNAME(target) + ".\n";
        target_message = QCTNAME(caster) + " sweeps " + caster->query_possessive()
            + " hands across " + caster->query_possessive() + " body in a "
            + "flourish and causes the sand to rise up from the ground. With "
            + "a quick flick, " + caster->query_pronoun() + " sends the "
            + "shower of tiny particles towards you.\n";
        watcher_message = QCTNAME(caster) + " sweeps " + caster->query_possessive()
            + " hands across " + caster->query_possessive() + " body in a "
            + "flourish and causes the sand to rise up from the ground. With "
            + "a quick flick, " + caster->query_pronoun() + " sends the "
            + "shower of tiny particles towards " + QTNAME(target) + ".\n";
        break;
    }
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
fireball_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The blue flaming sphere barely misses you and "
            + "explodes in a loud bang behind you.\n";
        watcher_message = "The blue flaming sphere barely misses "
            + QTNAME(target) + " and explodes in a loud bang behind "
            + target->query_objective() + ".\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The flaming sphere gets close enough to you to "
                + "sear your " + hitloc_desc + ", but barely hurts you.\n";
            watcher_message = "The flaming sphere gets close enough to "
                + QTNAME(target) + " to sear " + target->query_possessive()
                + " " + hitloc_desc + ", but barely hurts "
                + target->query_objective() + ".\n";
            break;
            
        case 1..10:
            target_message = "The ball of flame strike you gently, but the "
                + "scorching heat from the sphere causes your skin to break "
                + "out in bubbling painful boils.\n";
            watcher_message = "The ball of flame strikes " + QTNAME(target)
                + " gently, but the scorching heat from the sphere causes "
                + caster->query_possessive() + " skin to break out in "
                + "bubbling painful boils.\n";
            break;
            
        case 11..30:
            target_message = "You try and avoid the flaming ball of "
                + "fire, but it manages to strike you squarely on "
                + "your " + hitloc_desc + ", causing great pain.\n";
            watcher_message = QCTNAME(target) + " tries to avoid "
                + "the flaming ball of fire, but it manages to strike "
                + target->query_objective() + " squarely on "
                + target->query_possessive() + " " + hitloc_desc + ", causing "
                + "great pain.\n";
            break;
            
        case 31..60:
            target_message = "The incinerating fire of the ball of flame "
                + "intensifies as it gets closer to you, splits into two "
                + "and manages to strike you twice on your " + hitloc_desc
                + ", charring your skin and boiling your blood.\n";
            watcher_message = "The incinerating fire of the ball of flame "
                + "intensifies as it gets closer to " + QTNAME(target) + ", "
                + "splits into two and manages to strike "
                + target->query_objective() + " twice on "
                + target->query_possessive() + " " + hitloc_desc + ", "
                + "charring " + target->query_possessive() + " skin and "
                + "boiling " + target->query_possessive() + " blood.\n";
            break;
            
        default:
            target_message = "The brightly burning blue ball of flame gets "
                + "larger and larger as it approaches you, completely "
                + "enveloping you in its incandescent flames and scorching "
                + "your body to its very core.\n";
            watcher_message = "The brightly burning blue ball of flame gets "
                + "larger and larger as it approaches " + QTNAME(target)
                + ", completely enveloping " + target->query_objective()
                + " in its incandescent flames and scorching "
                + target->query_possessive() + " body to its very core.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
flamethrow_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The streaking bands of flame shoot right past you, "
            + "barely missing you.\n";
        watcher_message = "The streaking bands of flame shoot right past "
            + QTNAME(target) + " barely missing " + caster->query_objective()
            + ".\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The blazing streak of fire hits you squarely "
                + "on your " + hitloc_desc + ", but dissipates immediately, "
                + "barely singeing your hair.\n";
            watcher_message = "The blazing streak of fire hits " + QTNAME(target)
                + " squarely on " + target->query_possessive() + " "
                + hitloc_desc + ", but dissipates immediately, barely "
                + "singeing " + target->query_possessive() + " hair.\n";
            break;
            
        case 1..10:
            target_message = "The streams of infernal fire seem to come from "
                + "all directions and incinerate your " + hitloc_desc
                + ", scorching you heavily.\n";
            watcher_message = "The streams of infernal fire seem to come "
                + "from all directions and incinerate " + QTPNAME(target)
                + " " + hitloc_desc + ", scorching " + target->query_objective()
                + " heavily.\n";
            break;
            
        case 11..30:
            target_message = "The massive heat from the streams of flame "
                + "start to boil your blood as the flames envelop you "
                + "in their incinerating heat.\n";
            watcher_message = "The massive heat from the streams of flame "
                + "start to boil " + QTPNAME(target) + " blood as the "
                + "flames envelop " + target->query_objective() + " in "
                + "their incinerating heat.\n";
            break;
            
        case 31..60:
            target_message = "The streams of flame assail you and form "
                + "circular rings around you before constricting you "
                + "and almost severing your " + hitloc_desc + " through "
                + "the forceful burning fire.\n";
            watcher_message = "The streams of flame assail " + QTNAME(target)
                + " and form circular rings around " + target->query_objective()
                + " before constricting " + target->query_objective()
                + " and almost severing " + target->query_possessive()
                + " " + hitloc_desc + " through the forceful burning fire.\n";
            break;
            
        default:
            target_message = "Multiple streams of fire combine into a single "
                + "large stream and it forcefully wallop you and punches "
                + "a hole straight through your " + hitloc_desc + " and out "
                + "the other side, leaving you charred and broken.\n";
            watcher_message = "Multiple streams of fire combine into a single "
                + "large stream and it forcefully wallops " + QTNAME(target)
                + " and punches a hole straight through " + target->query_possessive()
                + " " + hitloc_desc + " and out the other side, leaving "
                + target->query_objective() + " charred and broken.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
fire_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];
    
    switch (caster->query_prop(CHEIROPOTO_SUBELEMENT))
    {
    case 0:
        fireball_desc_damage(caster, target, phurt, hitloc_desc);
        break;
        
    case 1:
    default:
        flamethrow_desc_damage(caster, target, phurt, hitloc_desc);
        break;
    }    
}

public void
hail_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Hail stones fall all around you, but they all "
            + "miraculously miss you.\n";
        watcher_message = "Hail stones fall all around " + QTNAME(target)
            + ", but they all miraculously miss " + target->query_objective()
            + ".\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Hail stones rush by you, their scattered impact "
                + "only scratches your " + hitloc_desc + " causing little "
                + "injury.\n";
            watcher_message = "Hail stones rush by " + QTNAME(target) + ", "
                + "their scattered impact only scratches " + target->query_possessive()
                + " " + hitloc_desc + " causing little injury.\n";
            break;
            
        case 1..10:
            target_message = "Hail stones accurately strike your "
                + hitloc_desc + " piercing the skin leaving you with several "
                + "small painful wounds.\n";
            watcher_message = "Hail stones accurately strike " + QTPNAME(target)
                + " " + hitloc_desc + " piercing the skin leaving "
                + target->query_objective() + " with several small painful "
                + "wounds.\n";
            break;
            
        case 11..30:
            target_message = "The freezing cluster of hail stones tighten "
                + "into a razor-sharp icicle that impales your " + hitloc_desc
                + " in a gashing wound.\n";
            watcher_message = "The freezing cluster of hail stones tighten "
                + "into a razor-sharp icicle that impales " + QTPNAME(target)
                + " " + hitloc_desc + " in a gashing wound.\n";
            break;
            
        case 31..60:
            target_message = "A storm of hail stones cover your " + hitloc_desc 
                + " entirely and you feel your skin numbing as you see large "
                + "chunks of it break apart with a sickening crackle.\n";
            watcher_message = "A storm of hail stones cover " + QTPNAME(target)
                + " " + hitloc_desc + " entirely and you see large chunks "
                + "of " + target->query_possessive() + " skin break apart "
                + "with a sickening crackle.\n";
            break;
            
        default:
            target_message = "Hail stones both large and small smash into "
                + "you, hammering you unrelentingly and shattering "
                + "almost every bone in your body.\n";
            watcher_message = "Hail stones both large and small smash into "
                + QTNAME(target) + ", hammering " + target->query_objective()
                + " unrelentingly and shattering almost every bone in "
                + target->query_possessive() + " body.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
acid_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A sour smell fills your nostrils as the cluster of "
            + "greenish fluid flies by you and misses you completely.\n";
        watcher_message = "A sour smell fills the air as you watch a cluster "
            + "of greenish fluid fly by " + QTNAME(target) + " missing "
            + target->query_objective() + " completely.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The rotating cluster of greenish fluid almost "
                + "dissipates before covering your " + hitloc_desc + ", causing "
                + "slight tingling from the acidic burn.\n";
            watcher_message = "The rotating cluster of greenish fluid almost "
                + "dissipates before covering " + QTPNAME(target) + " "
                + hitloc_desc + ", causing a slight acidic burn.\n";
            break;
            
        case 1..10:
            target_message = "As the cluster of greenish fluid impacts your "
                + hitloc_desc + ", a sizzling sound alerts you to a burning "
                + "pain spreading from throughout your body.\n";
            watcher_message = "As the cluster of greenish fluid impacts "
                + QTPNAME(target) + " " + hitloc_desc + ", a sizzling sound "
                + "accompanies the acidic corrosion of "
                + target->query_possessive() + " flesh.\n";
            break;
            
        case 11..30:
            target_message = "The cluster of greenish fluid tightens into a "
                + "small ball as it approaches you and splashes your "
                + hitloc_desc + ", partially dissolving it as every drop "
                + "sears into you!\n";
            watcher_message = "The cluster of greenish fluid tightens into a "
                + "small ball as it approaches " + QTNAME(target) + " and "
                + "splashes " + target->query_possessive() + " " + hitloc_desc
                + ", partially dissolving it as every drop sears into "
                + target->query_objective() + ".\n";
            break;
            
        case 31..60:
            target_message = "The cluster of greenish fluid flies towards you "
                + "and expands as it builds its momentum. As it envelops you, "
                + "the large acidic cloud dissolves your " + hitloc_desc
                + " almost completely!\n";
            watcher_message = "The cluster of greenish fluid flies towards "
                + QTNAME(target) + " and expands as it builds its momentum. "
                + "As it envelops " + QTNAME(target) + ", the large "
                + "acidic cloud dissolves " + target->query_possessive()
                + " " + hitloc_desc + " almost completely!\n";
            break;
            
        default:
            target_message = "You look on in fear as the cluster of greenish "
                + "fluid expands and builds its momentum towards you. The "
                + "cloud envelops you completely and follows your every "
                + "movement shrivelling you terribly.\n";
            watcher_message = QCTNAME(target) + " looks on in fear as the "
                + "cluster of greenish fluid expands and builds its momentum "
                + "towards " + target->query_objective() + ". The cloud "
                + "envelops " + target->query_objective() + " completely "
                + "and follows " + target->query_possessive() + " every "
                + "movement shrivelling " + target->query_objective()
                + " terribly.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
water_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];
    
    switch (caster->query_prop(CHEIROPOTO_SUBELEMENT))
    {
    case 0:
        hail_desc_damage(caster, target, phurt, hitloc_desc);
        break;
        
    case 1:
    default:
        acid_desc_damage(caster, target, phurt, hitloc_desc);
        break;
    }    
}

public void
vortex_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "You feel an chilling gust of wind as the small "
            + "vortex flails by you, missing you completely.\n";
        watcher_message = "The small vortex flails by " + QTNAME(target)
            + ", missing " + target->query_objective() + " completely "
            + "and causing only a chilling gust of wind.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The small vortex swirls about uncontrollably and "
                + "rages past you producing several gusts of wind that pummel "
                + "your " + hitloc_desc + " numbing you slightly.\n";
            watcher_message = "The small vortex swirls about uncontrollably and "
                + "rages past " + QTNAME(target) + " producing several "
                + "gusts of wind that pummel " + target->query_possessive()
                + " " + hitloc_desc + " numbing " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 1..10:
            target_message = "With a fierce howl the vortex strikes you "
                + "forcefully and causes you to fall to the ground. You hear "
                + "a sharp crack as you fall to the ground and hurt "
                + "your " + hitloc_desc + ".\n";
            watcher_message = "With a fierce howl the vortex strikes "
                + QTNAME(target) + " forcefully and causes "
                + target->query_objective() + " to fall to the ground. You "
                + "hear a sharp crack as " + target->query_pronoun()
                + " falls to the ground and hurts " + target->query_possessive()
                + " " + hitloc_desc + ".\n";
            break;
            
        case 11..30:
            target_message = "The small vortex expands and envelops you "
                + "within its fierce gales, sending debris everywhere which "
                + "slams into your " + hitloc_desc + " bruising it horribly.\n";
            watcher_message = "The small vortex expands and envelops "
                + QTNAME(target) + " within its fierce gales, sending "
                + "debris everywhere which slams into " + target->query_possessive()
                + " " + hitloc_desc + " bruising it horribly.\n";
            break;
            
        case 31..60:
            target_message = "You try to avoid the approaching small vortex, but "
                + "it follows your every move and catches you in its twirling "
                + "fury. You spin around only to be lifted and mercilessly "
                + "hurtled into the ground sustaining mortal injury to your "
                + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) + " tries to avoid the "
                + "approaching small vortex, but it follows " + target->query_possessive()
                + " every move and catches " + target->query_objective()
                + " in its twirling fury. " + capitalize(target->query_pronoun())
                + " spins around only to be lifted and mercilessly "
                + "hurtled into the ground sustaining mortal injury to "
                + target->query_possessive() + " " + hitloc_desc + ".\n";
            break;
            
        default:
            target_message = "Despite your best efforts to escape it, the "
                + "gusting small vortex catches you within its twirling fury, "
                + "spinning you endlessly as it lifts you up and slams you "
                + "to the ground again and again.\n";
            watcher_message = "Despite " + target->query_possessive() + " "
                + "best efforts to escape it, the gusting small vortex "
                + "catches " + QTNAME(target) + " within its twirling "
                + "fury, spinning " + target->query_objective() + " endlessly "
                + "as it lifts " + target->query_objective() + " up and "
                + "slams " + target->query_objective() + " to the ground "
                + "again and again.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
electricity_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Small bolts of elecriticy crackle menacingly as "
            + "they fly by you, raising your hairs slightly.\n";
        watcher_message = "Small bolts of electricity crackle menacingly as "
            + "they fly by " + QTNAME(target) + ", raising "
            + target->query_possessive() + " slightly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Numerous small lightning bolts fly wide, missing you, "
                + "but one briefly crackles across your " + hitloc_desc 
                + " inflicting a superficial wound.\n";
            watcher_message = "Numerous small lightning bolts fly wide, missing "
                + QTNAME(target) + ", but one crackles across "
                + target->query_possessive() + " " + hitloc_desc
                + " inflicting a superficial wound.\n";
            break;
            
        case 1..10:
            target_message = "Sustained by accuracy and buildup, electrical "
                + "bolts shatter across your " + hitloc_desc + " opening "
                + "several painful burning wounds.\n";
            watcher_message = "Sustained by accuracy and buildup, electrical "
                + "bolts shatter across " + QTPNAME(target) + " "
                + hitloc_desc + " opening several painful burning wounds.\n";
            break;
            
        case 11..30:
            target_message = "Arcing electrical currents dance through the air "
                + "before striking your " + hitloc_desc + ", continuing their "
                + "dance around and through you for several agonizing "
                + "seconds as it hurts you thoroughly.\n";
            watcher_message = "Arcing electrical currents dance through the "
                + "air before striking " + QTPNAME(target) + " " + hitloc_desc
                + ", continuing their dance around and through "
                + target->query_objective() + " for several agonizing "
                + "seconds as it hurts " + target->query_objective()
                + " thoroughly.\n";
            break;
            
        case 31..60:
            target_message = "Bright blue arcs of electricity shimmer "
                + "violently before they coalesce into a single massive "
                + "light-blue bolt that hammers into your " + hitloc_desc
                + " and passes through you, causing you to tremble "
                + "in painful spasmodic response.\n";
            watcher_message = "Bright blue arcs of electricity shimmer "
                + "violently before they colesce into a single massive "
                + "light-blue bolt that hammers into " + QTPNAME(target)
                + " " + hitloc_desc + " and passes through "
                + target->query_objective() + ", causing "
                + target->query_objective() + " to tremble in painful "
                + "spasmodic response.\n";
            break;
            
        default:
            target_message = "Multiple arcs of electricity surround you and "
                + "bounce repeatedly from object to object, mercilessly "
                + "striking you everywhere and penetrating and dancing "
                + "across you in devastation. You convulse in terminal "
                + "agony.\n";
            watcher_message = "Multiple arcs of electrity surround "
                + QTNAME(target) + " and bounce repeatedly from object to "
                + "object, mercilessly striking " + target->query_objective()
                + " everywhere and penetrating and dancing across " 
                + target->query_objective() + " in devastation. " 
                + QCTNAME(target) + " convulses in terminal " + "agony.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
air_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];
    
    switch (caster->query_prop(CHEIROPOTO_SUBELEMENT))
    {
    case 0:
        vortex_desc_damage(caster, target, phurt, hitloc_desc);
        break;
        
    case 1:
    default:
        electricity_desc_damage(caster, target, phurt, hitloc_desc);
        break;
    }    
}

public void
earthquake_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message + "The reverberations in the ground make their way "
            + "towards you, but you feel nothing but minor trembles.\n";
        watcher_message = "The reverberations in the ground make their way "
            + "towards " + QTNAME(target) + ", but they don't seem to "
            + "affect " + target->query_objective() + ".\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The tremors of the earth reach you, causing you "
                + "to be nauseated.\n";
            watcher_message = "The tremors of the earth reach " + QTNAME(target)
                + ", causing " + target->query_objective() + " to be "
                + "nauseated.\n";
            break;
            
        case 1..10:
            target_message = "The ground beneath you rumbles and you try to "
                + "catch your footing, but you cannot maintain your balance "
                + "and fall upon some sharp rocks, hurting your " 
                + hitloc_desc + ".\n";
            watcher_message = "The ground beneath " + QTNAME(target)
                + " rumbles and " + target->query_pronoun() + " tries to catch "
                + target->query_possessive() + " footing, but "
                + target->query_pronoun() + " cannot maintain "
                + target->query_possessive() + " balance and falls upon some "
                + "sharp rocks, hurting " + target->query_possessive() 
                + " " + hitloc_desc + ".\n";
            break;
            
        case 11..30:
            target_message = "The reverberations reach you and increase in "
                + "intensity. Your whole body is shaken and the shaking "
                + "induces severe nausea. You try and maintain your balance "
                + "but fall, heavily injuring your " + hitloc_desc
                + " in the process.\n";
            watcher_message = "The reverberations reach " + QTNAME(target)
                + " and increase in intensity. " + QCTPNAME(target) + " "
                + "whole body is shaken and the shaking induces severe "
                + "nausea. " + capitalize(target->query_pronoun()) + " tries "
                + "to maintain " + target->query_possessive() + " balance "
                + "but falls instead, heavily injuring " + target->query_possessive()
                + " " + hitloc_desc + " in the process.\n";
            break;
            
        case 31..60:
            target_message = "Gaping fissures open in the ground beneath you "
                + "as searing steam escapes from the ground. You try and "
                + "jump out of the way, but the loose rocks from the "
                + "tremors severely injure your " + hitloc_desc + ".\n";
            watcher_message = "Gaping fissures open in the ground beneath "
                + QTNAME(target) + " as searing steam escapes from the "
                + "ground. " + capitalize(target->query_pronoun()) + " tries "
                + "to jump out of the way, but the loose rocks from the "
                + "tremors severely injure " + target->query_possessive()
                + " " + hitloc_desc + ".\n";
            break;
            
        default:
            target_message = "The ground you stand upon cracks under the force "
                + "of the reverberations and sunders, sending liquid lava "
                + "spewing out of the cracks. You are unable to avoid the magma, "
                + "and it lands upon you and consumes your flesh.\n";
            watcher_message = "The ground that " + QTNAME(target) + " stands "
                + "upon cracks under the force of the reverberations and sunders, "
                + "sending liquid lava spewing out of the cracks. " 
                + QCTNAME(target) + " is unable to avoid the magma, and the lava "
                + "lands upon " + target->query_objective() + " and consumes "
                + target->query_possessive() + " flesh.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
sand_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The tiny particles of sand flutter past you without "
            + "making an impact on you.\n";
        watcher_message = "The tiny particles of sand flutter past "
            + QTNAME(target) + " without making an impact on "
            + target->query_objective() + ".\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The tiny particles of sand strike you on your "
                + "face and barely scratch you.\n";
            watcher_message = "The tiny particles of sand strike "
                + QTNAME(target) + " on " + target->query_possessive()
                + " face and barely scratches " + target->query_objective()
                + ".\n";
            break;
            
        case 1..10:
            target_message = "Tiny particles of sand rush over your entire "
                + "body, forcing themselves into tiny crevices, digging into "
                + "you and causing great pain.\n";
            watcher_message = "Tiny particles of sand rush over " + QTPNAME(target)
                + " entire body, forcing themselves into tiny crevices, digging "
                + "into " + target->query_objective() + " and causing great "
                + "pain.\n";
            break;
            
        case 11..30:
            target_message = "The sand strikes your face and each particle "
                + "tears away at your skin, leaving bleeding, gaping "
                + "holes in your flesh.\n";
            watcher_message = "The sand strikes " + QTPNAME(target) + " face "
                + "and each particle tears away at " + target->query_possessive()
                + " skin, leaving bleeding, gaping holes in " 
                + target->query_possessive() + " flesh.\n";
            break;
            
        case 31..60:
            target_message = "You breathe just as the sand reaches you, "
                + "causing the sand to enter your throat. The particles "
                + "dig into your esophagael tract, causing you to bleed and "
                + "spit up massive amounts of blood.\n";
            watcher_message = QCTNAME(target) + " breathes just as the sand "
                + "reaches " + target->query_objective() + ", causing the "
                + "sand to enter " + target->query_possessive() + " throat. "
                + "The particles dig into " + target->query_possessive()
                + " esophagael tract, causing " + target->query_objective()
                + " to bleed and spit up massive amounts of blood.\n";
            break;
            
        default:
            target_message = "The tiny particles seem to multiply and become "
                + "a steady stream of sand that enshrouds your face. The "
                + "sand pours in through your nostrils and mouth into your "
                + "throat and fill your entire lungs with searing, painful "
                + "attacks until you are no longer able to breathe.\n";
            watcher_message = "The tiny particles seem to multiply and become "
                + "a steady stream of sand that enshrouds " + QTPNAME(target)
                + " face. The sand pours in through " + target->query_possessive()
                + " nostrils and into " + target->query_possessive() + " throat "
                + "and fills " + target->query_possessive() + " entire lungs "
                + "with searing, painful attacks until " + target->query_pronoun()
                + " is no longer able to breathe.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
earth_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];
    
    switch (caster->query_prop(CHEIROPOTO_SUBELEMENT))
    {
    case 0:
        earthquake_desc_damage(caster, target, phurt, hitloc_desc);
        break;
        
    case 1:
    default:
        sand_desc_damage(caster, target, phurt, hitloc_desc);
        break;
    }
}
