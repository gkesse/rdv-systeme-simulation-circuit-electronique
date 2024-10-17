#pragma once

#include "rdv_app_include.h"

class Variant : public QObject
{
    Q_OBJECT

public:
    class Type
    {
    public:
        enum Value
        {
            None,
            Int,          // Integer
            Raw,          // QByteArray
            Double,       // Real number
            String,       // Editable string
            Multiline,    // String that may contain linebreaks
            RichText,     // HTML formatted text
            Select,       // Selection of strings
            Combo,        // Editable combination of strings
            FileName,     // Filename on local filesystem
            Color,        // Color
            Bool,         // Boolean
            VarName,      // Variable name
            Port,         // Port name
            Pin,          // Pin name
            PenStyle,     // Pen Style
            PenCapStyle,  // Pen Cap Style
            SevenSegment, // Pin Map for Seven Segment Display
            KeyPad        // Pin Map for Keypad
        };
    };

public:
    Variant(const QString &id, Type::Value type);
    ~Variant() override;

    void setCaption(const QString &caption);
    void setToolbarCaption(const QString &caption);
    void setEditorCaption(const QString &caption);

private:
    QString m_toolbarCaption; // Short description shown in e.g. properties dialog
    QString m_editorCaption;  // Text displayed before the data entry widget in the toolbar
};
