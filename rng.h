#ifndef RNG_H
#define RNG_H

#include <random>

class RNG
{
public:
    RNG(float min = 0.0,
        float max = 1.0,
        float success = 0.6);
    RNG(float successPercentChance = 40.0);

    float minValue() const {return m_minValue;}
    float maxValue() const {return m_maxValue;}
    float successPercentChance() const {return
                ((m_maxValue - m_successValue)/(m_maxValue - m_minValue))*100;}
    float successValue() const {return m_successValue;}

    void setMinValue(float minValue);
    void setMaxValue(float maxValue);
    void setSuccessPercentChance(float percent);
    void setSuccessValue(float successValue);

    bool operator()();

private:
    std::uniform_real_distribution<> m_distribution;
    std::mt19937 m_prng;

    float m_minValue;
    float m_maxValue;
    float m_successValue;
};

#endif // RNG_H
