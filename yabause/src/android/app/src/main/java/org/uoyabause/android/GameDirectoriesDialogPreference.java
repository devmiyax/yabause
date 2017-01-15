package org.uoyabause.android;

import android.app.Activity;
import android.app.DialogFragment;
import android.app.FragmentTransaction;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Resources;
import android.os.Environment;
import android.preference.DialogPreference;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.BaseAdapter;
import android.widget.ListAdapter;

import org.uoyabause.android.tv.GameSelectFragment;

import java.io.File;
import java.util.ArrayList;

class DirectoryListAdapter extends BaseAdapter implements ListAdapter{

    private Context context;
    private ArrayList<String> _directoryList = new ArrayList<String>();

    ArrayList<String> getList(){ return _directoryList; }

    public DirectoryListAdapter(Context context) {
        this.context = context;
    }

    public void setDirectorytList(ArrayList<String> directoryList) {
        this._directoryList = directoryList;
    }

    @Override
    public int getCount() {
        return _directoryList.size();
    }

    @Override
    public Object getItem(int position) {
        return _directoryList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position; //_directoryList.get(position).getId();
    }

    public void addDirectory( String path ){
        _directoryList.add(path);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view = convertView;
        if (view == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = inflater.inflate(R.layout.game_directories_listitem, null);
        }
        ((TextView)view.findViewById(R.id.game_directory_item)).setText(_directoryList.get(position));

        Button deleteBtn = (Button)view.findViewById(R.id.button_delete);
        deleteBtn.setTag(position);
        deleteBtn.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                Integer position = (Integer)v.getTag();
                if( position != null ){
                    _directoryList.remove(position.intValue()); //or some other task
                    notifyDataSetChanged();
                    GameSelectFragment.refresh_level = 3;
                }
            }
        });

        return view;
    }
}
/**
 * Created by shinya on 2016/01/07.
 */
public class GameDirectoriesDialogPreference extends DialogPreference implements View.OnClickListener , FileDialog.DirectorySelectedListener {

    private YabauseSettings _context = null;
    DirectoryListAdapter adapter;
    ListView listView;
   // File currentRootDirectory = Environment.getExternalStorageDirectory();

    public GameDirectoriesDialogPreference(Context context) {
        super(context);
        InitObjects(context);
    }

    public GameDirectoriesDialogPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
        InitObjects(context);
    }

    @Override
    protected void onDialogClosed(boolean positiveResult) {
        if(positiveResult){
            String resultstring = "";
            ArrayList<String> list = adapter.getList();
            for( int i=0; i< list.size(); i++ ){
                resultstring += list.get(i);
                resultstring += ";";
            }
            String data = getPersistedString ("err");
            if( !data.equals(resultstring)){
                _context.setDireListChangeStatus(true);
            }
            persistString(resultstring);
        }
        super.onDialogClosed(positiveResult);
    }

    public GameDirectoriesDialogPreference(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        InitObjects(context);
    }

    public void setActivity( Activity a){
        _context = (YabauseSettings)a;
        _context.setDireListChangeStatus(false);
    }

    void InitObjects( Context context) {

        setDialogLayoutResource(R.layout.game_directories);
    }

    @Override
    protected void onBindDialogView(View view){
        ArrayList<String> list;
        list = new ArrayList<String>();
        String data = getPersistedString ("err");
        if( data.equals("err")){
            YabauseStorage yb = YabauseStorage.getStorage();
            list.add(yb.getGamePath());
        }else {
            String[] paths = data.split(";", 0);
            for( int i=0; i<paths.length; i++ ){
                list.add(paths[i]);
            }
        }

        listView = (ListView)view.findViewById(R.id.listView);
        adapter = new DirectoryListAdapter(_context);
        adapter.setDirectorytList(list);
        listView.setAdapter(adapter);

        View button = (Button) view.findViewById(R.id.button_add);
        button.setOnClickListener(this);

    }


    public void onClick(View v) {
        FileDialog fd = new FileDialog(_context,"");
        fd.setSelectDirectoryOption(true);
        fd.addDirectoryListener(this);
        fd.showDialog();
    }

    @Override
    public void directorySelected(File directory){
        adapter.addDirectory(directory.getAbsolutePath());
        adapter.notifyDataSetChanged();
        GameSelectFragment.refresh_level = 3;
    }

}
