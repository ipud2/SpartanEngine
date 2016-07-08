//= INCLUDES =================
#include "QDirectus3DWidget.h"
//============================

// CONSTRUCTOR/DECONSTRUCTOR =========================
QDirectus3DWidget::QDirectus3DWidget(QWidget *parent)
 : QWidget(parent) {

    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);

    InitializeEngine();
    Resize(this->size().width(), this->size().height());
}

QDirectus3DWidget::~QDirectus3DWidget()
{
    ShutdownEngine();
}

Socket* QDirectus3DWidget::GetEngineSocket()
{
    return m_socket;
}
//====================================================

//= OVERRIDDEN FUNCTIONS =============================
void QDirectus3DWidget::resizeEvent(QResizeEvent* evt)
{
    int width = evt->size().width();
    int height = evt->size().width();

    Resize(width, height);
}

void QDirectus3DWidget::paintEvent(QPaintEvent* evt)
{
    Render();
}
//===================================================

//= Engine functions ================================
void QDirectus3DWidget::InitializeEngine()
{
    // Create and initialize Directus3D
    m_engine = new Engine();
    HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
    HWND mainWindowHandle = (HWND)this->parentWidget()->winId();
    HWND widgetHandle = (HWND)this->winId();
    m_engine->Initialize(hInstance, mainWindowHandle, widgetHandle);

    // Get the socket
    m_socket = m_engine->GetSocket();
}

void QDirectus3DWidget::ShutdownEngine()
{
    m_engine->Shutdown();
    delete m_engine;
}

void QDirectus3DWidget::Render()
{
    m_socket->Run();
}

void QDirectus3DWidget::Resize(int width, int height)
{
    m_socket->SetViewport(width, height);
}
//===================================================