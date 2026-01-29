The new Blademasters.

The new files are presented here. The changes are summarized below. I
am not sure about timers in numbers, so I am ready to adjust to keep
combat aid to the level where the tax paid is 10% or less.

A. The new abilities:

1. bstudy

In the soul file blade_soul.c - allows to study an opponent
before fight, not during it. Then based on the combination of the
appraise enemy skill and the guild stat divided by five, there is a
determined randomness in comparison of hit location. The degree of
randomness is always at least 10%, but could be 100%.

The command also detects, to similar degree of randomness/error which
hitlocations seem to have no armour protection over them.

If an observer has AWARENESS skill to be 75 or above, they notice
being studied.

All the code is original.

> bstudy dummy
You notice it's the easiest to hit on the body, then, by a significant margin, 
    the legs, then the head, then the left arm or the right arm.
You also observe that the body, the legs, the head, the left arm and the right 
    arm appear to be unprotected.

CBAID: TBD. I wouldn't give it more than 0.5% - this is something that
can be figured out more or less empirically without the ability.

2. battack <hitlocation>

Targets the battack to a valid hitlocation of the enemy. Goes through
the regular routines to have hitloc query_hitloc_factor() established
at 85. The idea is to have the numbers tuned to combat aid of 48% (8%
tax)

Otherwise the preparation, the cooldown and any other code regarding
the attack has not been changed. The file is blade_attack.c .
Borrows some code from Zizuph's targeted smash for AA.

B. The new skills

Blademasters can now trade 'Appraise enemy' at the locations in
bladesmiths of Port Macdunn and Sa Morgan up to Superior
Craftsman. The expected tax will be 30/60 = 0.5%. 

C. The new items/rooms

There are two small alcoves behind the smithies in Port Macdunn and Sa
Morgan where the appraise enemy skill can be learned. Only
blademasters can enter there.

The shadow is unchanged. The help files will be updated after the
final reviews and verdicts.

In general the idea is to present a more tactical guild, and give the
members the sense of maintenance and involvement. One next potential
development is to give Blademasters who are also Smiths bonuses -
ability to forge blades with extra hit/pen, which only they can wield.
