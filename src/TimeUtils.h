/*
 * Copyright (c) 2006 Sean C. Rhea (srhea@srhea.net)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _TimeUtils_h
#define _TimeUtils_h

#include <QObject>
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QString>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QComboBox>

QString interval_to_str(double secs);  // output like 1h 2m 3s
double str_to_interval(QString s);     // convert 1h 2m 3s -> 3123.0 , e.g.
QString time_to_string(double secs);   // output like 1:02:03

/* takes a string containing an ISO 8601 timestamp and converts it to local time
*/
QDateTime convertToLocalTime(QString timestamp);

class DateRange : QObject
{
    Q_OBJECT

    public:
        DateRange(const DateRange& other);
        DateRange(QDate from = QDate(), QDate to = QDate(), QString name ="");
        DateRange& operator=(const DateRange &);
        QDate from, to;
        QString name;

    signals:
        void changed(QDate from, QDate to);
};

class DateSettingsEdit : public QWidget
{
    Q_OBJECT

    private:
        QWidget *parent;
        bool active;

        // editing components
        QRadioButton *radioSelected, *radioToday, *radioCustom, *radioLast, *radioFrom;
        QDateEdit *fromDateEdit, *toDateEdit, *startDateEdit;
        QDoubleSpinBox *lastn;
        QComboBox *lastnx;

    public:

        DateSettingsEdit(QWidget *parent);

        void setMode(int);
        int mode();

        // betweem from and to
        void setFromDate(QDate x) { fromDateEdit->setDate(x); }
        QDate fromDate() { return fromDateEdit->date(); }
        void setToDate(QDate x) { toDateEdit->setDate(x); }
        QDate toDate() { return toDateEdit->date(); }

        // start date till today
        void setStartDate(QDate x) { startDateEdit->setDate(x); }
        QDate startDate() { return startDateEdit->date(); }

        // last n of days/weeks/months/years
        int lastN() { return lastn->value(); }
        void setLastN(int x)  { lastn->setValue(x); }
        int lastNX() { return lastnx->currentIndex(); }
        void setLastNX(int x)  { lastnx->setCurrentIndex(x); }

    private slots:
        void setDateSettings();

    signals:
        void useStandardRange();
        void useThruToday();
        void useCustomRange(DateRange);

};

#endif // _TimeUtils_h
