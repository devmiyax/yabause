package org.uoyabause.android;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RatingBar;
import android.widget.TextView;

/**
 * Created by shinya on 2015/10/24.
 */
public class ReportDialog extends DialogFragment implements DialogInterface.OnClickListener,RatingBar.OnRatingBarChangeListener {

    RatingBar _GameStatusRating;
    TextView _rateText;
    EditText _edt;
    CheckBox _chk;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        LayoutInflater inflater = (LayoutInflater)getActivity().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View content = inflater.inflate(R.layout.report, null);
        _GameStatusRating = (RatingBar)content.findViewById(R.id.report_ratingBar);
        _GameStatusRating.setNumStars(5);
        _GameStatusRating.setRating(3.0f);
        _GameStatusRating.setStepSize(1.0f);
        _GameStatusRating.setOnRatingBarChangeListener(this);

        _edt =(EditText)content.findViewById(R.id.report_message);
        _chk =(CheckBox)content.findViewById(R.id.report_Screenshot);
        _rateText = (TextView)content.findViewById( R.id.report_rateString);
        onRatingChanged(_GameStatusRating,3.0f,false);
        builder.setView(content);

        builder.setMessage("Report emulation status of this game.")
                .setPositiveButton("Send", this)
                .setNegativeButton("Cancel",this);
        // Create the AlertDialog object and return it
        return builder.create();
    }

    @Override
    public void onClick(DialogInterface dialog, int which) {

        if( which == -1 ) {
            Yabause activity = (Yabause) getActivity();
            int rating = (int) _GameStatusRating.getRating();
            String message = _edt.getText().toString();
            activity.doReportCurrentGame(rating, message, _chk.isChecked());
        }else if( which == -2 ){
            Yabause activity = (Yabause) getActivity();
            activity.cancelReportCurrentGame();
        }else{

        }
    }

    @Override
    public void onRatingChanged(RatingBar ratingBar, float rating,
                                boolean fromUser) {
        int iRate = (int)rating;
        switch(iRate){
            case 0:
                _rateText.setText("This game does not boot.");
                break;
            case 1:
                _rateText.setText("This game boots to title screen, but game is not playable.");
                break;
            case 2:
                _rateText.setText("This game is playable, but there are many graphics and sound glitches.");
                break;
            case 3:
                _rateText.setText("This game is playable, but there are a few graphics and sound glitches.");
                break;
            case 4:
                _rateText.setText("This game runs almost perfectly.");
                break;
            case 5:
                _rateText.setText("This game runs perfectly and is confirmed to reach the ending.");
                break;
            default:
                break;
        }

    }
}
