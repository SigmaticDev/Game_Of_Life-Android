#include "rng.h"

RNG::RNG(float min, float max, float success) :
    m_distribution(min, max),
    m_prng(std::random_device{}()),
    m_minValue(min),
    m_maxValue(max),
    m_successValue(success)
{
}

RNG::RNG(float successPercentChance) :
    m_distribution(0.0, 1.0),
    m_prng(std::random_device{}()),
    m_minValue(0.0),
    m_maxValue(1.0),
    m_successValue((100 - successPercentChance)/100)
{
}

void RNG::setMinValue(float minValue)
{
    if (minValue < m_maxValue) m_minValue = minValue;

    return;
}

void RNG::setMaxValue(float maxValue)
{
    if (maxValue > m_minValue) m_maxValue = maxValue;

    return;
}

void RNG::setSuccessPercentChance(float percent)
{
    if (percent > 0.0 && percent < 100.0) {
        setMaxValue(1.0); // Repeated to account for case where m_maxValue
        setMinValue(0.0); // is already set to some value less than 0.0 or if
        setMaxValue(1.0); // m_minValue is set to a value greater than 1.0
        setMinValue(0.0);

        setSuccessValue((100 - percent)/100);
    }

    return;
}

void RNG::setSuccessValue(float successValue)
{
    if (successValue > m_minValue && successValue < m_maxValue) {
        m_successValue = successValue;
    }

    return;
}

bool RNG::operator ()()
{
    return m_distribution(m_prng) > m_successValue;
}
