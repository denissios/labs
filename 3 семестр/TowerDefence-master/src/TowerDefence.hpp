#ifndef __TOWER_DEFENCE_HPP_INCLUDED__
#define __TOWER_DEFENCE_HPP_INCLUDED__

#include <QtWidgets/QMainWindow>
#include <memory>
#include <chrono>

#include "Pos.hpp"

using namespace std::chrono_literals;

namespace Ui
{
    class TowerDefenceClass;
}

class QTimer;

namespace TowerDefence
{
    class Graphics;
    class Landscape;

    /*!
    \brief class for tower defence game
    */
    class TowerDefence final : public QMainWindow
    {
        Q_OBJECT

    private:
        inline static constexpr auto TIMER_INTERVAL{ 100ms };
        inline static constexpr auto BUTTON_SIZE{ 100 };

    private:
        /*!
        \brief event of keyboard by pressing on buttons
        \return void
        */
        void keyPressEvent(QKeyEvent* event) override;

        /*!
        \brief event of mouse by click
        \return void
        */
        void mousePressEvent(QMouseEvent* event) override;

        /*!
        \brief initializing widgets
        \return void
        */
        void initWidgets();

        /*!
        \brief initializing buttons
        \return void
        */
        void initButtons();

        /*!
        \brief update label of money
        \return void
        */
        void updateMoneyLabel(const int money);

        /*!
        \brief update all buttons
        \return void
        */
        void updateButtons();

        /*!
        \brief set position of buttons
        \return void
        */
        void setButtons(const PosF& pos);

        /*!
        \brief disable all buttons
        \return void
        */
        void disableButtons();

    public:
        TowerDefence(QWidget* parent = nullptr);

        ~TowerDefence() noexcept;

        void update();

    private:
        std::unique_ptr<Ui::TowerDefenceClass> m_ui;
        std::unique_ptr<QTimer>                m_timer;
        std::shared_ptr<Graphics>              m_graphics;
        std::shared_ptr<Landscape>             m_landscape;
    };
} // namespace TowerDefense
#endif /* !__TOWER_DEFENCE_HPP_INCLUDED__ */