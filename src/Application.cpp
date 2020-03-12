﻿#include "Decoder.hpp"
#include "Application.hpp"

Application::Application(int argc, char **argv)
    : QGuiApplication(argc, argv)
{
    decoder = new Decoder;
    connect(decoder, &Decoder::finished, this, [&](){
        decoder->deleteLater();
        decoder = nullptr;
    });

    decoder->start();
}

Application::~Application()
{
    if (decoder){
        decoder->requestInterruption();
    }
}

void Application::setupUi()
{
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
}