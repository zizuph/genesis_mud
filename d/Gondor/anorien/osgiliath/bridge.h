/*
 *	/d/Gondor/anorien/osgiliath/bridge.h
 *
 *	OSG_BRIDGE_NO_ATTACK:
 *		no attack yet, east bank held by Gondor
 *	OSG_BRIDGE_ATTACK_IMMINENT:
 *		attack imminent, as rq_stage >= RQ_OSGILIATH_ATTACK
 *	OSG_BRIDGE_ATTACK:
 *		attack under way
 *	OSG_BRIDGE_GONDOR_HEAD:
 *		after attack,
 *		Gondor scenario: Gondor bridgehead on east bank
 *	OSG_BRIDGE_MORGUL_HEAD:
 *		after attack,
 *		Morgul scenario: Morgul bridgehead on west bank
 *	OSG_BRIDGE_BRIDGE_BROKEN:
 *		after attack,
 *		standard scenario: bridge broken, no bridgeheads
 */
#ifndef GONDOR_OSGILIATH_BRIDGE
#define GONDOR_OSGILIATH_BRIDGE
#define OSG_BRIDGE_NO_ATTACK		  0
#define OSG_BRIDGE_ATTACK_IMMINENT	 10
#define OSG_BRIDGE_ATTACK		 15
#define OSG_BRIDGE_GONDOR_HEAD		 30
#define OSG_BRIDGE_MORGUL_HEAD		 50
#define OSG_BRIDGE_BRIDGE_BROKEN	100
#endif

