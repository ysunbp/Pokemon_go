#include "arena.h"

Arena::Arena(): MAX_BATTLE_TIME(1000), MAX_NUM_OF_ROUNDS(1000) {};

Trainer* Arena::battle(Trainer* attacker, Trainer* defender) {
    Kun** atKuns = attacker->getKunGroup().getKuns();
    Kun** deKuns = defender->getKunGroup().getKuns();

    int atKunCount = attacker->getKunGroup().getKunCount();
    int deKunCount = defender->getKunGroup().getKunCount();

    if (deKunCount <= 0) return attacker;
    if (atKunCount <= 0) return defender;

    int atCursor = 0, deCursor = 0;
    const clock_t begin_time = clock();
    while (clock() - begin_time < MAX_BATTLE_TIME) {
        CombatResult result = battle(atKuns[atCursor], deKuns[deCursor]);
        switch (result) {
            case ATTACKER_WINS:
                deCursor++;
                break;
            case DEFENDER_WINS:
                atCursor++;
                break;
            case ENDLESS:
                break;
            case DIETOGETHER:
                atCursor++;
                deCursor++;
                break;
        }
        if (deCursor >= deKunCount) return attacker;
        if (atCursor >= atKunCount) return defender;
    }
    return attacker;
}

CombatResult Arena::battle(Kun* attacker, Kun* defender) {

	if (!attacker || attacker->getHP() <= 0) {
		if (!defender || defender->getHP() <= 0) return DIETOGETHER;
		else return DEFENDER_WINS;
	} else if (!defender || defender->getHP() <= 0) return ATTACKER_WINS;

    for (int i=0;i<MAX_NUM_OF_ROUNDS;i++) {
        int atMove = (attacker->getMoveCount() <= 0) ? WATER_SPRAY : attacker->getMoveList()[i % attacker->getMoveCount()];
        int deMove = (defender->getMoveCount() <= 0) ? WATER_SPRAY : defender->getMoveList()[i % defender->getMoveCount()];
        double atAttack = attacker->getAttack();
        double atDefense = attacker->getDefense();
        double deAttack = defender->getAttack();
        double deDefense = defender->getDefense();

        switch (atMove) {
            case HYDRO_PUMP:
                atAttack *= 1.5;
                atDefense *= 0.7;
                break;
            default: break;
        }
        switch (deMove) {
            case HYDRO_PUMP:
                deAttack *= 1.5;
                deDefense *= 0.7;
                break;
            default: break;
        }

        double atDamage = (atAttack - deDefense) > 1 ? (atAttack - deDefense) : 1;
        double deDamage = (deAttack - atDefense) > 1 ? (deAttack - atDefense) : 1;

        double atHeal = 0, deHeal = 0;
        if (atMove == AQUA_RING) {
            atDamage = 0;
            atHeal = 5;
        }
        if (deMove == AQUA_RING) {
            deDamage = 0;
            deHeal = 5;
        }

        attacker->setHP(attacker->getHP() - deDamage + atHeal);
        defender->setHP(defender->getHP() - atDamage + deHeal);

        if (!attacker->isAlive() && !defender->isAlive()) return DIETOGETHER;
        else if (!attacker->isAlive()) return DEFENDER_WINS;
        else if (!defender->isAlive()) return ATTACKER_WINS;
    }
    return ENDLESS;
}
