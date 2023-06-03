#ifndef REGENPARITY_RECOVERED_HPP
#define REGENPARITY_RECOVERED_HPP


enum AttributeBuffType: int {};

class AttributeBuff {
    public:
    char filler1[48]; // 48
};

class InstantaneousAttributeBuff : public AttributeBuff {
    public:
    char filler2[8]; // 56
    InstantaneousAttributeBuff(float, AttributeBuffType);
};

class AttributeInstance {
    public:
    char filler[48]; // 48
    void* delegate; // 52
    float getCurrentValue() const;
    void addBuff(const AttributeBuff&);
};

class GameRuleId {
    public:
    GameRuleId(int);
};

class GameRules {
    public:
    bool getBool(GameRuleId) const;
};

class Level {
    public:
    int getDifficulty() const;
    GameRules* getGameRules() const;
};

enum ActorDamageCause: int {};

class ActorDamageSource {
    public:
    char filler1[8]; // 8
    ActorDamageSource(ActorDamageCause);
};

class Attribute;

class Actor {
    public:
    int getHealth() const;
    void heal(int);
    Level* getLevel() const;
    void hurt(const ActorDamageSource&, int, bool, bool);
    AttributeInstance* getMutableAttribute(const Attribute&);
};

class Player : public Actor {
    public:
    static Attribute HUNGER;
    static Attribute SATURATION;
    bool isHurt();
    void causeFoodExhaustion(float);
    /*InnerCore*/ float getSaturation() const;
    float getExhaustion() const;
};

class AttributeInstanceDelegate {
    public:
    char filler1[12]; // 12
    AttributeInstance* _getInstance() const;
    AttributeInstance* _getMutableInstance() const;
};

class HungerAttributeDelegate : public AttributeInstanceDelegate {
    public:
    int foodTimer; // 16
    char filler2[4]; // 20
    float prevFoodLevel; // 24
    Player* player; // 28
};


#endif //REGENPARITY_RECOVERED_HPP