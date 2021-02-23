#include "l_container.h"

L_Container::L_Container()
{

}

L_TaskObject &L_Container::operator[](int n)
{
    return *m_data[n];
}

void L_Container::fill(QVector<L_TaskObject *> &&ptr)
{
    m_data.clear();
    for(auto&& a: ptr)
    a->getTape(m_data);
}

void L_Container::next()
{
    m_current = (m_current + 1) % m_data.size();
}

void L_Container::previous()
{
    m_current = (m_current + m_data.size() - 1) % m_data.size();
}
