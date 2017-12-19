#pragma once

// ����� �������
// ����� �������� ���������� ������ ������������ �������� ������� 
class Timer
{
    unsigned long m_startTime;
    unsigned long m_finishTime;
    bool m_isOverflow;

public:
    explicit Timer();
    ~Timer();

    void start(const unsigned long period);
    bool isFinished() const;
};
