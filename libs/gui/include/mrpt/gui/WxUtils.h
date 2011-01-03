/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                   http://mrpt.sourceforge.net/                            |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */
#ifndef  MRPT_WX_UTILS_H
#define  MRPT_WX_UTILS_H

#include <mrpt/utils/utils_defs.h>
#include <mrpt/utils/CImage.h>
#include <mrpt/utils/CConfigFileBase.h>
#include <mrpt/utils/CConfigFileMemory.h>
#include <mrpt/synch.h>
#include <mrpt/gui/keycodes.h>

#include <mrpt/gui/link_pragmas.h>

#if MRPT_HAS_WXWIDGETS

#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
#include <wx/msgdlg.h>
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/progdlg.h>
#include <wx/imaglist.h>
#include <wx/busyinfo.h>
#include <wx/log.h>
#include <wx/textdlg.h>
#include <wx/dirdlg.h>
#include <wx/colordlg.h>
#include <wx/dcmemory.h>
#include <wx/app.h>
#include <wx/pen.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/radiobox.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/dc.h>
#include <wx/dcclient.h>

#endif

namespace mrpt
{
	namespace gui
	{
#if MRPT_HAS_WXWIDGETS


#ifndef _U
#	ifdef wxUSE_UNICODE
#		define _U(x) wxString::From8BitData(x)
#	else
#		define _U(x) (x)
#	endif
#endif


		/** Create a wxImage from a MRPT image. The new object must be freed by the user when not required anymore.
		  * \sa MRPTImage2wxImage
		  */
		wxImage GUI_IMPEXP * MRPTImage2wxImage( const mrpt::utils::CImage &img );

		/** Create a wxBitmap from a MRPT image. The new object must be freed by the user when not required anymore.
		  * \sa MRPTImage2wxImage
		  */
		wxBitmap GUI_IMPEXP * MRPTImage2wxBitmap( const mrpt::utils::CImage &img );

#if MRPT_HAS_OPENCV
		/** Create a wxImage from a IPL image. The new object must be freed by the user when not required anymore.
		  * \sa IplImage2wxImage
		  */
		wxImage GUI_IMPEXP * IplImage2wxImage( void* img );
#endif

		/** Create a MRPT image from a wxImage. The new object must be freed by the user when not required anymore.
		  *  It is recommended to use wxImage2MRPTImagePtr instead since smart pointers are safer to manage.
		  * \sa wxImage2MRPTImage, wxImage2MRPTImagePtr
		  */
		mrpt::utils::CImage GUI_IMPEXP * wxImage2MRPTImage( const wxImage &img );

		/** Create a MRPT image from a wxImage. The new object is returned as a smart pointer to a CImage object.
		  * \sa wxImage2MRPTImage
		  */
		mrpt::utils::CImagePtr GUI_IMPEXP wxImage2MRPTImagePtr( const wxImage &img );

		/** Extracts the key modifiers from a wxKeyEvent */
		mrptKeyModifier keyEventToMrptKeyModifier( const wxKeyEvent &ev );

		/** A custom control to display the bitmap and avoid flicker
		  */
		class GUI_IMPEXP wxMRPTImageControl : public wxPanel
		{
		protected:
			wxBitmap *m_img;
			mrpt::synch::CCriticalSection	m_img_cs;

			wxPoint m_last_mouse_point, m_last_mouse_click;
			mrpt::synch::CCriticalSection	m_mouse_cs;

		public:
			wxMRPTImageControl(	wxWindow *parent,wxWindowID winID,int x, int y, int width, int height);
			virtual ~wxMRPTImageControl();

			void AssignImage(wxBitmap *img); //!< Assigns this image. This object has the ownship of the image and will delete it when appropriate. Remember to call Refresh to display the image.
			void AssignImage(const mrpt::utils::CImage &img); //!< Assigns this image. Remember to call Refresh to display the image.
			void GetBitmap(wxBitmap &bmp);

			void OnPaint(wxPaintEvent &ev);
			void OnMouseMove(wxMouseEvent& ev);
			void OnMouseClick(wxMouseEvent& ev);

			void OnEraseBackground(wxEraseEvent &ev) { /* Do nothing */ }
		};
		// end wxMRPTImageControl  -----------

		/** A panel to select the camera input from all the formats supported by MRPT */
		class GUI_IMPEXP CPanelCameraSelection: public wxPanel
		{
		public:

			CPanelCameraSelection(wxWindow* parent,wxWindowID id=wxID_ANY);
			virtual ~CPanelCameraSelection();

			void readConfigIntoVideoSourcePanel(
				const std::string &sect,
				const mrpt::utils::CConfigFileBase *cfg ) const;

			void writeConfigFromVideoSourcePanel(
				const std::string &sect,
				mrpt::utils::CConfigFileBase *cfg ) const;

		//(*Declarations(CPanelCameraSelection)
		wxNotebook* pagesCameras;
		wxPanel* Panel1;
		wxPanel* Panel6;
		wxPanel* pnSwissRanger;
		wxTextCtrl* edCustomCamConfig;
		wxCheckBox* cbSR_chRange;
		wxCheckBox* cbSR_chIntensity;
		wxTextCtrl* edIPcamURL;
		wxCheckBox* cbSR_ch3D;
		wxRadioBox* rbSR_usb;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxButton* btnBrowseVideo;
		wxPanel* Panel2;
		wxCheckBox* cbKinect_3D;
		wxStaticText* StaticText3;
		wxPanel* Panel4;
		wxTextCtrl* edRawlogFile;
		wxButton* btnBrowseRawlog;
		wxChoice* cbOpencvResolution;
		wxPanel* Panel5;
		wxStaticText* StaticText8;
		wxPanel* Panel3;
		wxStaticText* StaticText7;
		wxCheckBox* cbGrayscale;
		wxChoice* cbOpencvCamType;
		wxCheckBox* cbKinect_Depth;
		wxPanel* pnKinect;
		wxRadioBox* rbBumblebeeSel;
		wxTextCtrl* edRawlogLabel;
		wxStaticText* StaticText4;
		wxCheckBox* cbSR_chConf;
		wxCheckBox* cbKinect_Int;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		wxTextCtrl* edSR_IP;
		wxStaticText* StaticText6;
		wxCheckBox* cbBumblebeeRectif;
		wxButton* btnBrowseRawlogDir;
		wxTextCtrl* edRawlogImgDir;
		wxSpinCtrl* opencvCamIndex;
		wxStaticText* StaticText9;
		wxStaticText* StaticText11;
		wxTextCtrl* edVideoFile;
		//*)

	protected:

		//(*Identifiers(CPanelCameraSelection)
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT6;
		static const long ID_CHOICE2;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL1;
		static const long ID_PANEL3;
		static const long ID_TEXTCTRL6;
		static const long ID_PANEL4;
		static const long ID_STATICTEXT8;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON7;
		static const long ID_PANEL5;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON8;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL7;
		static const long ID_BUTTON9;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL8;
		static const long ID_STATICTEXT11;
		static const long ID_PANEL6;
		static const long ID_RADIOBOX1;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_PANEL7;
		static const long ID_RADIOBOX2;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_PANEL1;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX9;
		static const long ID_PANEL8;
		static const long ID_NOTEBOOK1;
		static const long ID_CHECKBOX2;
		//*)

		private:

			//(*Handlers(CPanelCameraSelection)
			//*)
			void OnbtnBrowseVideoClick(wxCommandEvent& event);
			void OnbtnBrowseRawlogClick(wxCommandEvent& event);
			void OnbtnBrowseRawlogDirClick(wxCommandEvent& event);

			DECLARE_EVENT_TABLE()
		};
		// end   -----------

		/** Auxiliary structures used internally to mrpt */
		namespace detail
		{
			struct TReturnAskUserOpenCamera
			{
				mrpt::utils::CConfigFileMemory  selectedConfig;
				bool  accepted_by_user;
			};
		}

#endif

    } // End of namespace
} // End of namespace

#endif
